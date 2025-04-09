#pragma once
#include <opencv2/opencv.hpp>

struct AiLearnTools
{
public:
	static void SaveImage(cv::Mat frame, std::string learnInfoSign, bool isDad, int cameraNum);
	static QString SaveImagePath(std::string learnInfoSign);
	static QString SaveDataImagePath(std::string learnInfoSign, bool isBad, int cameraNum, std::string dateTimeStr);
	static QString SaveDataImageTranPath(std::string learnInfoSign, std::string dateTimeStr);
	static QString SaveDataImageValPath(std::string learnInfoSign, std::string dateTimeStr);
};