#include "ime_ModelEngine.h"

#include "yolov5v6_seg_trt.h"

namespace rw
{
    namespace ime
    {
        ProcessRectanglesResult ConvertPyRecMaskResultToProcessRectanglesResult(PyRecMaskResult& pyRecMaskResult)
        {
            ProcessRectanglesResult processRectanglesResult;
            processRectanglesResult.left_top = std::make_pair(pyRecMaskResult.left, pyRecMaskResult.top);
            processRectanglesResult.right_bottom = std::make_pair(pyRecMaskResult.right, pyRecMaskResult.bottom);
            processRectanglesResult.classId = pyRecMaskResult.classID;
            processRectanglesResult.track_id = pyRecMaskResult.track_id;
            processRectanglesResult.label_len = pyRecMaskResult.label_len;
            processRectanglesResult.mask_b = pyRecMaskResult.mask_b;
            processRectanglesResult.mask_g = pyRecMaskResult.mask_g;
            processRectanglesResult.mask_r = pyRecMaskResult.mask_r;
            processRectanglesResult.score = pyRecMaskResult.score;
            processRectanglesResult.label_text = std::string(pyRecMaskResult.label_text);
            return processRectanglesResult;
        }

        ModelEngine::ModelEngine(std::string modelPath, std::string nameFilePath)
        {
            _modelPath = modelPath;
            _nameFilePath = nameFilePath;
            _index = yolov5v6_seg_trt_create((char*)(modelPath.c_str()), (char*)(nameFilePath.c_str()), 0.25, 0.25, 0.45, 0.5, 0, 1);
            if (_index < 0) {
                _isCreated = false;
                throw std::runtime_error("Failed to create task with error code: " + std::to_string(_index));
            }
            _isCreated = true;
        }

        ModelEngine::~ModelEngine()
        {
            if (_isCreated) {
                yolov5v6_seg_trt_destroy(_index);
            }
        }

        bool ModelEngine::ProcessMask(cv::Mat& img, cv::Mat& resultMat, cv::Mat& maskMat,
            std::vector<ProcessRectanglesResult>& vecRecogResult)
        {
            try
            {
                std::vector<PyRecMaskResult> vecrecogresult;
                yolov5v6_seg_trt_process_mask(_index, img, resultMat, maskMat, vecrecogresult);
                vecRecogResult.clear();
                for (auto& pyRecMaskResult : vecrecogresult)
                {
                    vecRecogResult.push_back(ConvertPyRecMaskResultToProcessRectanglesResult(pyRecMaskResult));
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
