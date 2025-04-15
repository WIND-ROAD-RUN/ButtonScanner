#pragma once
#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>
#include <utility>
#include "utils.h"

using namespace std;

using RESULT_INFO = std::pair<int, std::string>;

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

class YOLOV5V62Seg
{
public:
    explicit YOLOV5V62Seg(std::nullptr_t) {};
    YOLOV5V62Seg(const std::string& modelPath,
                 const std::string& _name_path,
                 const int _threadnum,
                 const bool& isGPU);

	void LetterBox(const cv::Mat& image, cv::Mat& outImage,
		cv::Vec4d& params, //[ratio_x,ratio_y,dw,dh]
		const cv::Size& newShape = cv::Size(640, 640),
		bool autoShape = false,
		bool scaleFill = false,
		bool scaleUp = true,
		int stride = 32,
		const cv::Scalar& color = cv::Scalar(114, 114, 114));

    bool detect(cv::Mat& srcImg, std::vector<OutputSeg>& output, float nmsThreshold, float boxThreshold, float classThreshold, float maskThreshold);
private:

    Ort::Env env{nullptr};
    Ort::SessionOptions sessionOptions{nullptr};
    Ort::Session session{nullptr};

	Ort::Value transform(const cv::Mat& mat_rs); // without resize

	void GetMask(const cv::Mat& maskProposals, const cv::Mat& maskProtos, std::vector<OutputSeg>& output, const MaskParams& maskParams);
	void GetMask2(const cv::Mat& maskProposals, const cv::Mat& maskProtos, OutputSeg& output, const MaskParams& maskParams);

	const char* input_name = nullptr;
	std::vector<const char*> input_node_names;
    std::size_t input_tensor_size = 1;
	std::vector<int64_t> input_node_dims; // 1 input only.
	std::vector<float> input_values_handler;
	Ort::MemoryInfo memory_info_handler = Ort::MemoryInfo::CreateCpu(
		OrtArenaAllocator, OrtMemTypeDefault);
	std::vector<const char*> output_node_names;
	std::vector<std::vector<int64_t>> output_node_dims; // >=1 outputs
	int num_outputs = 1;
	int _netWidth = 640;
	int _netHeight = 640;
	static constexpr const float mean_val = 0.f;
	static constexpr const float scale_val = 1.0 / 255.f;
    std::vector<RESULT_INFO>    m_pvecName;	//Ãû³Æ
};