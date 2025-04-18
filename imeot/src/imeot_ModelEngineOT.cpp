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
			result.center_x = result.left_top.first+(result.right_bottom.first - result.left_top.first) / 2;
			result.center_y = result.left_top.second+(result.right_bottom.second - result.left_top.second) / 2;
			result.classID = yolov5ObbXResult.classID;
			result.label_len = yolov5ObbXResult.label_len;
			result.score = yolov5ObbXResult.score;
			result.label_text = yolov5ObbXResult.label_text;
			result.width = std::abs(result.left_top.first - result.right_bottom.first);
			result.height =std::abs(result.left_top.second - result.right_bottom.second);
			result.angle = yolov5ObbXResult.angle;
			return result;
		}

		ModelEngineOT::ModelEngineOT(std::string modelPath, std::string nameFilePath)
		{

#ifdef NDEBUG // 仅在 Debug 模式下禁用以下代码
			try
			{
				_modelPath = modelPath;
				_nameFilePath = nameFilePath;
				_index = tensorrt_yolo_onnx_multask_create(modelPath.c_str(), nameFilePath.c_str(),0.1);
				if (_index < 0) {
					_isCreated = false;
					throw std::runtime_error("Failed to create task with error code: " + std::to_string(_index));
				}
				_isCreated = true;
			}
			catch (const std::exception& ex)
			{
				// 捕获标准库异常并记录异常信息
				std::cerr << "Standard exception caught: " << ex.what() << std::endl;
			}
			catch (...)
			{
				// 捕获未知异常
				std::cerr << "Unknown exception caught." << std::endl;
			}
#else
			
#endif
			
			
		}

		ModelEngineOT::~ModelEngineOT()
		{

#ifdef NDEBUG // 仅在 Debug 模式下禁用以下代码
			if (_isCreated) {
				tensorrt_yolo_onnx_multask_destroy(_index);
			}
#else

#endif

		}

		bool ModelEngineOT::ProcessMask(cv::Mat& img, cv::Mat& resultMat, std::vector<ProcessRectanglesResultOT>& result)
		{
#ifdef NDEBUG // 仅在 Debug 模式下禁用以下代码
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
#else
			return true;
#endif

		}
	}
}
