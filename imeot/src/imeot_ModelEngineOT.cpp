#include "imeot_ModelEngineOT.h"

#include"tensorrt_yolo_onnx_multask.h"

namespace rw
{
	namespace imeot
	{
		static ProcessRectanglesResultOT convertYolov5ObbXResulttoProcessRectanglesResultOT(const Yolov5ObbXResult & yolov5ObbXResult)
		{
			ProcessRectanglesResultOT result;
			result.left_top.first = yolov5ObbXResult.left;
			result.left_top.second = yolov5ObbXResult.top;
			result.right_bottom.first = yolov5ObbXResult.right;
			result.right_bottom.second = yolov5ObbXResult.bottom;
			result.center_x = yolov5ObbXResult.center_x;
			result.center_y = yolov5ObbXResult.center_y;
			result.classID = yolov5ObbXResult.classID;
			result.label_len = yolov5ObbXResult.label_len;
			result.score = yolov5ObbXResult.score;
			result.label_text = yolov5ObbXResult.label_text;
			result.width = yolov5ObbXResult.width;
			result.height = yolov5ObbXResult.height;
			result.angle = yolov5ObbXResult.angle;
			return result;
		}

		ModelEngineOT::ModelEngineOT(std::string modelPath, std::string nameFilePath)
		{
			_modelPath = modelPath;
			_nameFilePath = nameFilePath;
			_index = tensorrt_yolo_onnx_multask_create(modelPath.c_str(), nameFilePath.c_str());
			if (_index < 0) {
				_isCreated = false;
				throw std::runtime_error("Failed to create task with error code: " + std::to_string(_index));
			}
			_isCreated = true;
		}

		ModelEngineOT::~ModelEngineOT()
		{
			if (_isCreated) {
				tensorrt_yolo_onnx_multask_destroy(_index);
			}
		}

		bool ModelEngineOT::ProcessMask(cv::Mat& img, cv::Mat& resultMat, std::vector<ProcessRectanglesResultOT>& result)
		{
			try
			{
				std::vector<Yolov5ObbXResult> vecrecogresult;
			
				tensorrt_yolo_onnx_multask_process(_index, img, resultMat, vecrecogresult);
				for (auto& yolov5ObbXResult : vecrecogresult)
				{
					result.push_back(convertYolov5ObbXResulttoProcessRectanglesResultOT(yolov5ObbXResult));
				}
				return true;
			}
			catch (...)
			{
				return false;
			}
		}
	}
}
