#pragma once
#include <opencv2/opencv.hpp>

struct AiLearnTools
{
public:
	static void SaveImage(cv::Mat frame, std::string learnInfoSign, std::string dateTimeStr, bool isBad, int cameraNum);
	static void SaveYoloText(std::string learnInfoSign, std::string dateTimeStr, bool isBad, int checkType, int centerX, int centerY, int width, int height, int imageWidth, int imageHeight);
	static std::string SaveYoloDataYaml(std::string learnInfoSign);
	static QImage  cvMat2QImage(const cv::Mat& mat);
	static void MakeDir(QString path);
	static void MoveImageToDataSet(std::string learnInfoSign, bool isSeg);

private:
	static QString SaveImagePath(std::string learnInfoSign);
	static QString SaveDataImagePath(std::string learnInfoSign, bool isBad, int cameraNum, std::string dateTimeStr);
	static QString SaveDataImageTranPath(std::string learnInfoSign);
	static QString SaveDataImageValPath(std::string learnInfoSign);
	static QString	SaveDataLabelTranPath(std::string learnInfoSign);
	static QString	SaveDataLabelValPath(std::string learnInfoSign);
	static void CopyDirectory(const QString& srcPath, const QString& dstPath);
};