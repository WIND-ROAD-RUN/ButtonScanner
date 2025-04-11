#include "stdafx.h"
#include "AiLearnTools.h"
#include <windows.h>
#include <qstring.h>
#include <qfileinfo.h>
#include <PathGlobalStruct.h>
#include <qdir.h>
#include <opencv2/opencv.hpp> 
#include <fstream>
#include <iostream>
#include <Shlwapi.h>
#include <filesystem> 

void AiLearnTools::SaveImage(cv::Mat frame, std::string learnInfoSign, std::string dateTimeStr, bool isBad, int cameraNum)
{
	QImage qImage = cvMat2QImage(frame);

	QString saveImagePath = SaveImagePath(learnInfoSign);
	MakeDir(saveImagePath);
	qImage.save(saveImagePath, "jpg");

	QString saveDataImagePath = SaveDataImagePath(learnInfoSign, isBad, cameraNum, dateTimeStr);
	MakeDir(saveDataImagePath);
	qImage.save(saveDataImagePath, "jpg");

	QString saveDataImageTranPath = SaveDataImageTranPath(learnInfoSign) + QString::fromStdString("\\" + dateTimeStr + ".jpg");
	MakeDir(saveDataImageTranPath);
	qImage.save(saveDataImageTranPath, "jpg");

	QString saveDataImageValPath = SaveDataImageValPath(learnInfoSign) + QString::fromStdString("\\" + dateTimeStr + ".jpg");
	MakeDir(saveDataImageValPath);
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

QString AiLearnTools::SaveDataImageTranPath(std::string learnInfoSign)
{
	return QString::fromStdString(PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataTranImages);
}

QString AiLearnTools::SaveDataImageValPath(std::string learnInfoSign)
{
	return QString::fromStdString(PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataValImages);
}

void AiLearnTools::MakeDir(QString path)
{
	/*QFileInfo file(path);
	if (!file.exists()) {*/
	QDir dir = QFileInfo(path).absoluteDir();
	if (!dir.exists()) {
		dir.mkpath(".");
	}
	//}
}

void AiLearnTools::SaveYoloText(std::string learnInfoSign, std::string dateTimeStr, bool  isBad, int checkType, int centerX, int centerY, int width, int height, int imageWidth, int imageHeight)
{
	std::string classId = isBad ? "0" : "1";
	//normalization��һ��
	auto norCenterX = (double)centerX / (double)imageWidth;
	auto norCenterY = (double)centerY / (double)imageHeight;
	auto norWidth = (double)width / (double)imageWidth;
	auto norHeight = (double)height / (double)imageHeight;


	auto textStr = classId + " " +
		std::to_string(norCenterX) + " " + std::to_string(norCenterY) + " "
		+ std::to_string(norWidth) + " " + std::to_string(norHeight);

	//��Segment����mask
	if (checkType == 1)
	{
		using Point = std::pair<double, double>;
		std::vector< Point> points;
		points.reserve(31);

		double angleStep = 2 * M_PI / 30;

		//����뾶
		auto r = (norHeight + (norWidth - norHeight) / 2) / 2;

		for (int i = 0; i < 30; i++) {
			double theta = i * angleStep;
			double x = norCenterX + r * std::cos(theta);
			double y = norCenterY + r * std::sin(theta);
			points.push_back(Point{ x, y });
		}
		points.push_back(points[0]);

		textStr += " ";
		for (int i = 0; i < 31; i++) {
			textStr += std::to_string(points[i].first) + "_" + std::to_string(points[i].second);
			if (i != 30)
				textStr += ",";
		}
	}
	auto tranPath = PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataTranLabel + "\\" + dateTimeStr + ".txt";
	MakeDir(QString::fromStdString(tranPath));
	std::ofstream tranOfs(tranPath);
	tranOfs << textStr;
	tranOfs.close();

	auto valPath = PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataValLabel + "\\" + dateTimeStr + ".txt";
	MakeDir(QString::fromStdString(valPath));
	std::ofstream valOfs(valPath);
	valOfs << textStr;
	valOfs.close();
}

std::string AiLearnTools::SaveYoloDataYaml(std::string learnInfoSign)
{
	char currentPathChar[MAX_PATH];
	GetModuleFileNameA(NULL, currentPathChar, MAX_PATH);
	std::filesystem::path currentPath = currentPathChar;
	std::string currentDirPath = currentPath.parent_path().string();

	std::string dataYamlStr = "";
	dataYamlStr += "tran: " + currentDirPath + "\\" + SaveDataImageTranPath(learnInfoSign).toStdString();
	dataYamlStr += "\r\n";
	dataYamlStr += "val: " + currentDirPath + "\\" + SaveDataImageValPath(learnInfoSign).toStdString();
	dataYamlStr += "\r\n\r\n";
	dataYamlStr += "nc: 2";
	dataYamlStr += R"(names: ["bad","good"])";

	std::string savePath = currentDirPath + "\\" + PathGlobalStruct::AiLearnYoloDataYaml;
	MakeDir(QString::fromStdString(savePath));
	std::ofstream ofs(savePath);
	ofs << dataYamlStr;
	ofs.close();

	return savePath;
}


QImage AiLearnTools::cvMat2QImage(const cv::Mat& mat) {
	// 1. ���������Ч��
	if (mat.empty()) {
		qWarning("cvMat2QImage: Input cv::Mat is empty!");
		return QImage();
	}

	// 2. ����������ڴ棨��������ʧЧ��
	cv::Mat localMat;
	if (!mat.isContinuous()) {
		localMat = mat.clone();  // ǿ�������洢
	}
	else {
		localMat = mat;          // ֱ�����ã�����ȷ���ⲿ�����������ڣ�
	}

	// 3. ����ͨ����ת��
	switch (localMat.type()) {
		// 8-bit 1 channel (grayscale)
		// 
	// ����Ҷ�ͼ
	case CV_8UC1: {
		QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
		return image;
	}
				// �����ɫͼ
	case CV_8UC3: {
		// ע�⣺OpenCV �� BGR ת Qt �� RGB
		QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_BGR888);
		return image.rgbSwapped();
	}
				// ������� Alpha ͨ����ͼ
	case  CV_8UC4: {
		QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_ARGB32);
		return image;
	}
	default:
		qWarning("cvMat2QImage: Unsupported Mat type (depth=%d, channels=%d)",
			mat.depth(), mat.channels());
		return QImage();
	}
}