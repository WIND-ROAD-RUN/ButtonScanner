#pragma once

#include"ime_ModelEngineCore.h"

#include"opencv2/opencv.hpp"

namespace rw
{
    namespace ime //image model engine
    {
        class ModelEngineST
        {
        private:
            int _index{ -1 };
            std::string _modelPath;
            std::string _nameFilePath;
            bool _isCreated{ false };
        public:
            ModelEngineST(std::string modelPath, std::string nameFilePath);
            ~ModelEngineST();
        public:
            bool ProcessMask(cv::Mat& img, cv::Mat& resultMat, cv::Mat& maskMat, std::vector<ProcessRectanglesResultST>& vecRecogResult);
        };
    }
}
