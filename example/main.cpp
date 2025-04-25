#include"imeso_ModelEngineSO.h"
#include"opencv2/opencv.hpp"
#include"QDebug"

int main()
{
	std::string modelPath = R"(C:\Users\rw\Desktop\best.onnx)";
	std::string namePath = R"(C:\Users\rw\Desktop\index.names)";
	rw::imeso::ModelEngineSO engine(modelPath.c_str(), namePath.c_str());

	auto img=cv::imread(R"(C:\Users\rw\Desktop\1\NG20250417152301729.jpg)");
	cv::Mat resultMat;
	cv::Mat maskMat;
	std::vector<rw::imeso::ProcessRectanglesResultSO> result;
	engine.ProcessMask(img, resultMat, maskMat, result);
	cv::imshow("result", resultMat);
	cv::waitKey(0);
	qDebug() << "result size: " << result.size();
}