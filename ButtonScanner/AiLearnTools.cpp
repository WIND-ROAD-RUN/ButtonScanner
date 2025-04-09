#include "stdafx.h"
#include "AiLearnTools.h"
#include <qstring.h>
#include <qfileinfo.h>
#include <PathGlobalStruct.h>
#include <qdir.h>
#include <opencv2/opencv.hpp> 

void AiLearnTools::SaveImage(cv::Mat frame, std::string learnInfoSign, std::string dateTimeStr, bool isDad, int cameraNum)
{

	QImage qImage;

	// ����Ҷ�ͼ
	if (frame.type() == CV_8UC1) {
		QImage image(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_Grayscale8);
		qImage = image.copy();
	}
	// �����ɫͼ
	else if (frame.type() == CV_8UC3) {
		// ע�⣺OpenCV �� BGR ת Qt �� RGB
		QImage image(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_BGR888);
		qImage = image.rgbSwapped();
	}
	// ������� Alpha ͨ����ͼ
	else if (frame.type() == CV_8UC4) {
		QImage image(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_ARGB32);
		qImage = image.copy();
	}
	else {
		// ��֧�ֵĸ�ʽ
		throw std::invalid_argument("AiLearn����ͼƬ,��֧�ֵĸ�ʽ!");
	}

	QString saveImagePath = SaveImagePath(learnInfoSign);
	QFileInfo saveImageFile(saveImagePath);
	if (!saveImageFile.exists()) {
		QDir dir = QFileInfo(saveImagePath).absoluteDir();
		if (!dir.exists()) {
			dir.mkpath(".");
		}
	}
	/*QFile file(pathQt);
	if (file.open(QIODevice::WriteOnly)) {
		file.close();
	}*/
	qImage.save(saveImagePath, "jpg");

	QString saveDataImagePath = SaveDataImagePath(learnInfoSign, isDad, cameraNum, dateTimeStr);
	QFileInfo saveDataImageFile(saveDataImagePath);
	if (!saveDataImageFile.exists()) {
		QDir dir = QFileInfo(saveDataImagePath).absoluteDir();
		if (!dir.exists()) {
			dir.mkpath(".");
		}
	}
	qImage.save(saveDataImagePath, "jpg");

	QString saveDataImageTranPath = SaveDataImageTranPath(learnInfoSign, dateTimeStr);
	QFileInfo saveDataImageTranFile(saveDataImageTranPath);
	if (!saveDataImageTranFile.exists()) {
		QDir dir = QFileInfo(saveDataImageTranPath).absoluteDir();
		if (!dir.exists()) {
			dir.mkpath(".");
		}
	}
	qImage.save(saveDataImageTranPath, "jpg");

	QString saveDataImageValPath = SaveDataImageValPath(learnInfoSign, dateTimeStr);
	QFileInfo saveDataImageValFile(saveDataImageValPath);
	if (!saveDataImageValFile.exists()) {
		QDir dir = QFileInfo(saveDataImageValPath).absoluteDir();
		if (!dir.exists()) {
			dir.mkpath(".");
		}
	}
	qImage.save(saveDataImageValPath, "jpg");


}

QString AiLearnTools::SaveImagePath(std::string learnInfoSign)
{
	return   QString::fromStdString(PathGlobalStruct::AiLearnImage + "\\" + learnInfoSign + ".jpg");
}

QString AiLearnTools::SaveDataImagePath(std::string learnInfoSign, bool isBad, int cameraNum, std::string dateTimeStr)
{
	if (isBad) {
		return QString::fromStdString(PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataBad + std::to_string(cameraNum) + "\\" + dateTimeStr + ".jpg");
	}
	else {
		return QString::fromStdString(PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataGood + std::to_string(cameraNum) + "\\" + dateTimeStr + ".jpg");
	}
}

QString AiLearnTools::SaveDataImageTranPath(std::string learnInfoSign, std::string dateTimeStr)
{
	return QString::fromStdString(PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataTran + "\\" + dateTimeStr + ".jpg");
}

QString AiLearnTools::SaveDataImageValPath(std::string learnInfoSign, std::string dateTimeStr)
{
	return QString::fromStdString(PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataVal + "\\" + dateTimeStr + ".jpg");
}

void AiLearnTools::SaveYoloText(std::string learnInfoSign, std::string dateTimeStr,int step, int checkType, int centerX, int centerY, int width, int height)
{
	auto classId = step == 1 ? "0" : "1";

	std::ofstream outFile("output.txt");
}

