#pragma once


#include<string>
#include"opencv2/opencv.hpp"

#include"imeso_ModelEngineSOCode.h"

namespace rw
{
	namespace imeso
	{
        class ModelEngineOT
        {
        private:
            int _index{ -1 };
            std::string _modelPath;
            std::string _nameFilePath;
            bool _isCreated{ false };
        public:
            ModelEngineOT(std::string modelPath, std::string nameFilePath);
            ~ModelEngineOT();
        public:
            bool ProcessMask(cv::Mat& img, cv::Mat& resultMat, cv::Mat maskMat,std::vector<ProcessRectanglesResultSO>& result);
        };

	}
}
