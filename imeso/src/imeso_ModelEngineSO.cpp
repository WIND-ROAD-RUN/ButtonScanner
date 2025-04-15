#include"imeso_ModelEngineSO.h"


#include"yolov5v6_seg_ort.h"

namespace rw
{
	namespace imeso
	{
		static ProcessRectanglesResultSO convertRecMaskResultToProcessRectanglesResultSO(const RecMaskResult& yolov5ObbXResult)
		{
			ProcessRectanglesResultSO result;
			result.left_top.first = yolov5ObbXResult.left;
			result.left_top.second = yolov5ObbXResult.top;
			result.right_bottom.first = yolov5ObbXResult.right;
			result.right_bottom.second = yolov5ObbXResult.bottom;
			result.classID = yolov5ObbXResult.classID;
			result.track_id = yolov5ObbXResult.track_id;
			result.label_len = yolov5ObbXResult.label_len;
			result.mask_id = yolov5ObbXResult.mask_id;
			result.score = yolov5ObbXResult.score;
			result.label_text = yolov5ObbXResult.label_text;
			return result;
		}

		ModelEngineOT::ModelEngineOT(std::string modelPath, std::string nameFilePath)
		{
			_modelPath = modelPath;
			_nameFilePath = nameFilePath;
			_index = yolov5v6_seg_ort_create(modelPath.c_str(), nameFilePath.c_str());
			if (_index < 0) {
				_isCreated = false;
				throw std::runtime_error("Failed to create task with error code: " + std::to_string(_index));
			}
			_isCreated = true;
		}

		ModelEngineOT::~ModelEngineOT()
		{
			if (_isCreated) {
				yolov5v6_seg_ort_destroy(_index);
			}
		}

		bool ModelEngineOT::ProcessMask(cv::Mat& img, cv::Mat& resultMat, cv::Mat maskMat,
			std::vector<ProcessRectanglesResultSO>& result)
		{
			try
			{
				std::vector<RecMaskResult> vecrecogresult;

				yolov5v6_seg_ort_process(_index, img, resultMat, maskMat, vecrecogresult);
				for (auto& yolov5ObbXResult : vecrecogresult)
				{
					result.push_back(convertRecMaskResultToProcessRectanglesResultSO(yolov5ObbXResult));
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