#pragma once

#include<string>
#include"opencv2/opencv.hpp"

#include"imeso_ModelEngineSOCode.h"

namespace rw
{
	namespace imeso
	{
		class ModelEngineSO
		{
		private:
			int _index{ -1 };
			std::string _modelPath;
			std::string _nameFilePath;
			bool _isCreated{ false };
		public:
			ModelEngineSO(std::string modelPath, std::string nameFilePath);
			~ModelEngineSO();
		public:
			bool ProcessMask(cv::Mat& img, cv::Mat& resultMat, cv::Mat maskMat, std::vector<ProcessRectanglesResultSO>& result);
		};
	}
}
