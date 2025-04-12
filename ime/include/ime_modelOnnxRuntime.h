#pragma once

#include"ime_ModelEngineCore.h"

#include"opencv2/opencv.hpp"

namespace rw
{
    namespace ime //image model engine
    {

        class ModelEngineOnnxRuntime 
        {
        private:
            int _index{ -1 };
            std::string _modelPath;
            std::string _nameFilePath;
            bool _isCreated{ false };
        public:
            ModelEngineOnnxRuntime(std::string modelPath, std::string nameFilePath);
            ~ModelEngineOnnxRuntime();
        public:
            bool ProcessMask(cv::Mat& img, cv::Mat& resultMat, std::vector<ProcessRectanglesResultOnnx>& vecRecogResult);
        };
    }
}
