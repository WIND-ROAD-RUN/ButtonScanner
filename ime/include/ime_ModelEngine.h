#pragma once

#include"ime_ModelEngineCore.h"

#include"opencv2/opencv.hpp"

namespace rw
{
    namespace ime //image model engine
    {
        class ModelEngine
        {
        private:
            int _index{ -1 };
            std::string _modelPath;
            std::string _nameFilePath;
            bool _isCreated{ false };
        public:
            ModelEngine(std::string modelPath, std::string nameFilePath);
            ~ModelEngine();
        public:
            bool ProcessMask(cv::Mat& img, cv::Mat& resultMat, cv::Mat& maskMat, std::vector<ProcessRectanglesResult>& vecRecogResult);
        };
    }
}
