#ifndef COMMON_FUN_H_
#define COMMON_FUN_H_

#include <vector>
#include "NvInfer.h"
#include <opencv2/opencv.hpp>

struct OutputSeg {
	int id;             //clss id
	float confidence;   //confident
	cv::Rect box;       //rect box
	cv::Mat boxMask;
};

struct MaskParams {
	int segChannels = 32;
	int segWidth = 160;
	int segHeight = 160;
	int netWidth = 640;
	int netHeight = 640;
	float maskThreshold = 0.5;
	cv::Size srcImgShape;
	cv::Vec4d params;
};

template <typename T>
T VectorProduct(const std::vector<T>& v)
{
	return std::accumulate(v.begin(), v.end(), 1, std::multiplies<T>());
};

void GetMask(const cv::Mat& maskProposals, const cv::Mat& maskProtos, std::vector<OutputSeg>& output, const MaskParams& maskParams)
{
	int seg_channels = maskParams.segChannels;
	int net_width = maskParams.netWidth;
	int seg_width = maskParams.segWidth;
	int net_height = maskParams.netHeight;
	int seg_height = maskParams.segHeight;
	float mask_threshold = maskParams.maskThreshold;
	cv::Vec4f params = maskParams.params;
	cv::Size src_img_shape = maskParams.srcImgShape;

	cv::Mat protos = maskProtos.reshape(0, { seg_channels,seg_width * seg_height });

	cv::Mat matmul_res = (maskProposals * protos).t();
	cv::Mat masks = matmul_res.reshape(output.size(), { seg_width,seg_height });
	vector<cv::Mat> maskChannels;
	split(masks, maskChannels);
	for (int i = 0; i < output.size(); ++i) {
		cv::Mat dest, mask;
		//sigmoid
		cv::exp(-maskChannels[i], dest);
		dest = 1.0 / (1.0 + dest);

		cv::Rect roi(int(params[2] / net_width * seg_width), int(params[3] / net_height * seg_height), int(seg_width - params[2] / 2), int(seg_height - params[3] / 2));
		dest = dest(roi);
		resize(dest, mask, src_img_shape, cv::INTER_NEAREST);

		//crop
		cv::Rect temp_rect = output[i].box;
		mask = mask(temp_rect) > mask_threshold;
		output[i].boxMask = mask;
	}
}


void GetMask2(const cv::Mat& maskProposals, const cv::Mat& maskProtos, OutputSeg& output, const MaskParams& maskParams)
{
	int seg_channels = maskParams.segChannels;
	int net_width = maskParams.netWidth;
	int seg_width = maskParams.segWidth;
	int net_height = maskParams.netHeight;
	int seg_height = maskParams.segHeight;
	float mask_threshold = maskParams.maskThreshold;
	cv::Vec4f maskparams = maskParams.params;
	cv::Size src_img_shape = maskParams.srcImgShape;

	cv::Rect temp_rect = output.box;
	//crop from mask_protos
	int rang_x = floor((temp_rect.x * maskparams[0] + maskparams[2]) / net_width * seg_width);
	int rang_y = floor((temp_rect.y * maskparams[1] + maskparams[3]) / net_height * seg_height);
	int rang_w = ceil(((temp_rect.x + temp_rect.width) * maskparams[0] + maskparams[2]) / net_width * seg_width) - rang_x;
	int rang_h = ceil(((temp_rect.y + temp_rect.height) * maskparams[1] + maskparams[3]) / net_height * seg_height) - rang_y;

	rang_w = MAX(rang_w, 1);
	rang_h = MAX(rang_h, 1);
	if (rang_x + rang_w > seg_width) {
		if (seg_width - rang_x > 0)
			rang_w = seg_width - rang_x;
		else
			rang_x -= 1;
	}
	if (rang_y + rang_h > seg_height) {
		if (seg_height - rang_y > 0)
			rang_h = seg_height - rang_y;
		else
			rang_y -= 1;
	}

	vector<cv::Range> roi_rangs;
	roi_rangs.push_back(cv::Range(0, 1));
	roi_rangs.push_back(cv::Range::all());
	roi_rangs.push_back(cv::Range(rang_y, rang_h + rang_y));
	roi_rangs.push_back(cv::Range(rang_x, rang_w + rang_x));

	//crop
	cv::Mat temp_mask_protos = maskProtos(roi_rangs).clone();
	cv::Mat protos = temp_mask_protos.reshape(0, { seg_channels,rang_w * rang_h });
	cv::Mat matmul_res = (maskProposals * protos).t();
	cv::Mat masks_feature = matmul_res.reshape(1, { rang_h,rang_w });
	cv::Mat dest, mask;

	//sigmoid
	cv::exp(-masks_feature, dest);
	dest = 1.0 / (1.0 + dest);

	int left = floor((net_width / seg_width * rang_x - maskparams[2]) / maskparams[0]);
	int top = floor((net_height / seg_height * rang_y - maskparams[3]) / maskparams[1]);
	int width = ceil(net_width / seg_width * rang_w / maskparams[0]);
	int height = ceil(net_height / seg_height * rang_h / maskparams[1]);

	resize(dest, mask, cv::Size(width, height), cv::INTER_NEAREST);
	mask = mask(temp_rect - cv::Point(left, top)) > mask_threshold;
	output.boxMask = mask;
}

void nms_and_mask(std::vector<OutputSeg>& output, float* det_blob, float* mask_blob,
	nvinfer1::Dims out_dims_det, nvinfer1::Dims out_dims_mask, cv::Vec4d params,
	cv::Mat& img, int input_W, int input_H, float box_thresh = 0.24, float cls_thresh=0.25, float nms_thresh = 0.45, float mask_thresh = 0.5) {
	std::vector<int> classIds;
	std::vector<float> confidences;
	std::vector<cv::Rect> boxes;
	std::vector<vector<float>> picked_proposals;  //output0[:,:, 5 + _className.size():net_width] to cal the mask
	float r_w = input_W / (img.cols * 1.0);
	float r_h = input_H / (img.rows * 1.0);
	int class_num = out_dims_det.d[2] - 5 - 32;
	for (int boxs_idx = 0; boxs_idx < out_dims_det.d[1]; boxs_idx++)
	{
		const int basic_pos = boxs_idx * out_dims_det.d[2];
		float box_score = det_blob[basic_pos + 4];
		if (box_score < box_thresh) {
			continue;
		}
		cv::Mat scores(1, class_num, CV_32FC1, &det_blob[basic_pos + 5]);
		cv::Point classIdPoint;
		double max_class_socre;
		minMaxLoc(scores, 0, &max_class_socre, 0, &classIdPoint);
		max_class_socre = (float)max_class_socre;
		if (max_class_socre > cls_thresh)
		{
			float x = (det_blob[basic_pos + 0] - params[2]) / params[0];  //x
			float y = (det_blob[basic_pos + 1] - params[3]) / params[1];  //y
			float w = det_blob[basic_pos + 2] / params[0];  //w
			float h = det_blob[basic_pos + 3] / params[1];  //h
			int left = MAX(int(x - 0.5 * w + 0.5), 0);
			int top = MAX(int(y - 0.5 * h + 0.5), 0);

			vector<float> temp_proto(det_blob + basic_pos + 5 + class_num, det_blob + basic_pos + out_dims_det.d[2]);
			picked_proposals.push_back(temp_proto);

			classIds.push_back(classIdPoint.x);
			confidences.push_back(box_score * max_class_socre);
			boxes.push_back(cv::Rect(left, top, int(w + 0.5), int(h + 0.5)));
		}
	}

	//nms
	float nmsScoreThreshold = box_thresh * cls_thresh;
	vector<int> nms_result;
	cv::dnn::NMSBoxes(boxes, confidences, nmsScoreThreshold, nms_thresh, nms_result);

	std::vector<vector<float>> temp_mask_proposals;
	cv::Rect holeImgRect(0, 0, img.cols, img.rows);
	for (int i = 0; i < nms_result.size(); ++i) {
		int idx = nms_result[i];
		OutputSeg result;
		result.id = classIds[idx];
		result.confidence = confidences[idx];
		result.box = boxes[idx] & holeImgRect;
		temp_mask_proposals.push_back(picked_proposals[idx]);
		output.push_back(result);
	}

	vector<int> mask_protos_shape = { out_dims_mask.d[0], out_dims_mask.d[1], out_dims_mask.d[2], out_dims_mask.d[3] };
	cv::Mat mask_protos = cv::Mat(mask_protos_shape, CV_32F, mask_blob);
	//int size[4] = { out_dims_mask.d[0], out_dims_mask.d[1], out_dims_mask.d[2], out_dims_mask.d[3] };
	//cv::Mat maskmat = cv::Mat::zeros(4, size, CV_32FC1);
	////注意，memcpy是拷贝字节，这里是拷贝float，float是4字节
	//memcpy(maskmat.data, mask_blob, out_dims_mask.d[0] * out_dims_mask.d[1] * out_dims_mask.d[2] * out_dims_mask.d[3]*4);

	if (temp_mask_proposals.size() <= 0)
	{
		return;
	}

	MaskParams mask_params;
	mask_params.params = params;
	mask_params.srcImgShape = img.size();
	mask_params.segChannels = out_dims_mask.d[1];
	mask_params.segWidth = out_dims_mask.d[2];
	mask_params.segHeight = out_dims_mask.d[3];
	mask_params.netWidth = input_W;
	mask_params.netHeight = input_H;
	mask_params.maskThreshold = mask_thresh;
	cv::Mat mask_proposals;
	for (int i = 0; i < temp_mask_proposals.size(); ++i)
		mask_proposals.push_back(cv::Mat(temp_mask_proposals[i]).t());
	GetMask(mask_proposals, mask_protos, output, mask_params);
}

void nms_and_mask_1(std::vector<OutputSeg>& output, float* det_blob, float* mask_blob,
	nvinfer1::Dims out_dims_det, nvinfer1::Dims out_dims_mask, cv::Vec4d params,
	cv::Mat& img, int input_W, int input_H, float box_thresh = 0.25, float cls_thresh = 0.25, float nms_thresh = 0.45, float mask_thresh = 0.5) {
	std::vector<int> classIds;
	std::vector<float> confidences;
	std::vector<cv::Rect> boxes;
	std::vector<vector<float>> picked_proposals;  //output0[:,:, 5 + _className.size():net_width] to cal the mask
	float r_w = input_W / (img.cols * 1.0);
	float r_h = input_H / (img.rows * 1.0);
	int class_num = out_dims_det.d[2] - 5 - 32;
	for (int boxs_idx = 0; boxs_idx < out_dims_det.d[1]; boxs_idx++)
	{
		const int basic_pos = boxs_idx * out_dims_det.d[2];
		float box_score = det_blob[basic_pos + 4];
		if (box_score < box_thresh) {
			continue;
		}
		cv::Mat scores(1, class_num, CV_32FC1, &det_blob[basic_pos + 5]);
		cv::Point classIdPoint;
		double max_class_socre;
		minMaxLoc(scores, 0, &max_class_socre, 0, &classIdPoint);
		max_class_socre = (float)max_class_socre;
		if (max_class_socre > cls_thresh)
		{
			float x = (det_blob[basic_pos + 0] - params[2]) / params[0];  //x
			float y = (det_blob[basic_pos + 1] - params[3]) / params[1];  //y
			float w = det_blob[basic_pos + 2] / params[0];  //w
			float h = det_blob[basic_pos + 3] / params[1];  //h
			int left = MAX(int(x - 0.5 * w + 0.5), 0);
			int top = MAX(int(y - 0.5 * h + 0.5), 0);

			vector<float> temp_proto(det_blob + basic_pos + 5 + class_num, det_blob + basic_pos + out_dims_det.d[2]);
			picked_proposals.push_back(temp_proto);

			classIds.push_back(classIdPoint.x);
			confidences.push_back(box_score * max_class_socre);
			boxes.push_back(cv::Rect(left, top, int(w + 0.5), int(h + 0.5)));
		}
	}

	//nms
	float nmsScoreThreshold = box_thresh * cls_thresh;
	vector<int> nms_result;
	cv::dnn::NMSBoxes(boxes, confidences, nmsScoreThreshold, nms_thresh, nms_result);

	std::vector<vector<float>> temp_mask_proposals;
	cv::Rect holeImgRect(0, 0, img.cols, img.rows);
	for (int i = 0; i < nms_result.size(); ++i) {
		int idx = nms_result[i];
		OutputSeg result;
		result.id = classIds[idx];
		result.confidence = confidences[idx];
		result.box = boxes[idx] & holeImgRect;
		temp_mask_proposals.push_back(picked_proposals[idx]);
		output.push_back(result);
	}

	if (temp_mask_proposals.size() <= 0)
	{
		return;
	}

	vector<int> mask_protos_shape = { out_dims_mask.d[0], out_dims_mask.d[1], out_dims_mask.d[2], out_dims_mask.d[3] };
	cv::Mat mask_protos = cv::Mat(mask_protos_shape, CV_32F, mask_blob);
	//int size[4] = { out_dims_mask.d[0], out_dims_mask.d[1], out_dims_mask.d[2], out_dims_mask.d[3] };
	//cv::Mat mask_protos = cv::Mat::zeros(4, size, CV_32FC1);
	////注意，memcpy是拷贝字节，这里是拷贝float，float是4字节
	//memcpy(mask_protos.data, mask_blob, out_dims_mask.d[0] * out_dims_mask.d[1] * out_dims_mask.d[2] * out_dims_mask.d[3]*4);

	MaskParams mask_params;
	mask_params.params = params;
	mask_params.srcImgShape = img.size();
	mask_params.segChannels = out_dims_mask.d[1];
	mask_params.segWidth = out_dims_mask.d[2];
	mask_params.segHeight = out_dims_mask.d[3];
	mask_params.netWidth = input_W;
	mask_params.netHeight = input_H;
	mask_params.maskThreshold = mask_thresh;
	for (int i = 0; i < temp_mask_proposals.size(); ++i)
	{
		GetMask2(cv::Mat(temp_mask_proposals[i]).t(), mask_protos, output[i], mask_params);
	}
}
#endif COMMON_FUN_H_