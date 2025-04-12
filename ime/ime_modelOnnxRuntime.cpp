#include"ime_modelOnnxRuntime.h"

#include"yolov5_det_ort_hasptr.h"



namespace rw
{
    namespace ime //image model engine
    {
        static ProcessRectanglesResultOnnx ConvertRecTrackResultToProcessRectanglesResult(const RecTrackResult & source) {
            ProcessRectanglesResultOnnx result;
            result.left_top.first = source.left;
            result.left_top.second = source.top;
            result.right_bottom.first = source.right;
            result.right_bottom.second = source.bottom;
            result.classID = source.classID;
            result.track_id = source.track_id;
            result.score = source.score;
            result.label_text = std::string(source.label_text);
            return result;

        }

        ModelEngineOnnxRuntime::ModelEngineOnnxRuntime(std::string modelPath, std::string nameFilePath)
        {
            _modelPath = modelPath;
            _nameFilePath = nameFilePath;
            _index = yolov5_det_onnxtr_hasptr_create((char*)(modelPath.c_str()), (char*)(nameFilePath.c_str()), 0.25, 0.45);
            if (_index < 0) {
                _isCreated = false;
                throw std::runtime_error("Failed to create task with error code: " + std::to_string(_index));
            }
            _isCreated = true;

        }
        ModelEngineOnnxRuntime::~ModelEngineOnnxRuntime()
        {
            if (_isCreated) {
                yolov5_det_onnxtr_hasptr_destroy(_index);
            }
        }

        bool ModelEngineOnnxRuntime::ProcessMask(cv::Mat& img, cv::Mat& resultMat, cv::Mat& maskMat, std::vector<ProcessRectanglesResultOnnx>& result)
        {
            try
            {
                std::vector<RecTrackResult> vecrecogresult;
                yolov5_det_onnxtr_hasptr_process(_index, img, resultMat, vecrecogresult);
                for (auto& pyRecMaskResult : vecrecogresult)
                {
                    result.push_back(ConvertRecTrackResultToProcessRectanglesResult(pyRecMaskResult));
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
