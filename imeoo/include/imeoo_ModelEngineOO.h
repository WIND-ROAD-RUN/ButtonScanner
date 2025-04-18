#pragma once

#include"imeoo_ModelEngineOOCore.h"

#include"opencv2/opencv.hpp"

namespace rw
{
	namespace imeoo
	{
		class ModelEngineOO
		{
		private:
			int _index{ -1 };
			std::string _modelPath;
			std::string _nameFilePath;
			bool _isCreated{ false };
		public:
			ModelEngineOO(std::string modelPath, std::string nameFilePath);
			~ModelEngineOO();
		public:
			bool ProcessMask(cv::Mat& img, cv::Mat& resultMat, std::vector<ProcessRectanglesResultOO>& result);
		};
	}
}
