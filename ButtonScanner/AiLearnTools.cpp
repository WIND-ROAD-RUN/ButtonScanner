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



void AiLearnTools::MoveImageToDataSet(std::string learnInfoSign,bool isSeg)
{
	//定义文件夹
	QDir tranImageDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "datasets\\mydataset\\train\\images");
	QDir tranLableDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "datasets\\mydataset\\train\\labels");

	QDir valImageDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "datasets\\mydataset\\val\\images");
	QDir valLableDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "datasets\\mydataset\\val\\labels");

	QDir tesImageDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "datasets\\mydataset\\tes");

	if (isSeg) {
		QDir tranImageDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "segdatasets\\mydataset\\train\\images");
		QDir tranLableDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "segdatasets\\mydataset\\train\\labels");

		QDir valImageDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "segdatasets\\mydataset\\val\\images");
		QDir valLableDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "segdatasets\\mydataset\\val\\labels");

		QDir tesImageDir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "segdatasets\\mydataset\\tes");
	}

	//删除文件夹
	tranImageDir.rmdir(tranImageDir.absolutePath());
	tranLableDir.rmdir(tranLableDir.absolutePath());

	valImageDir.rmdir(valImageDir.absolutePath());
	valLableDir.rmdir(valLableDir.absolutePath());

	tesImageDir.rmdir(tesImageDir.absolutePath());

	//创建文件夹
	tranImageDir.mkdir(".");
	tranLableDir.mkdir(".");

	valImageDir.mkdir(".");
	valLableDir.mkdir(".");

	tesImageDir.mkdir(".");

	//复制文件
	CopyDirectory(SaveDataImageTranPath(learnInfoSign), tranImageDir.absolutePath());
	CopyDirectory(SaveDataLabelTranPath(learnInfoSign), tranLableDir.absolutePath());

	CopyDirectory(SaveDataImageValPath(learnInfoSign), valImageDir.absolutePath());
	CopyDirectory(SaveDataLabelValPath(learnInfoSign), valLableDir.absolutePath());

	CopyDirectory(SaveDataImageValPath(learnInfoSign), tesImageDir.absolutePath());
}
void AiLearnTools::SaveYoloText(std::string learnInfoSign, std::string dateTimeStr, bool  isBad, int checkType, int centerX, int centerY, int width, int height, int imageWidth, int imageHeight)
{
	std::string classId = isBad ? "0" : "1";
	//normalization归一化
	auto norCenterX = (double)centerX / (double)imageWidth;
	auto norCenterY = (double)centerY / (double)imageHeight;
	auto norWidth = (double)width / (double)imageWidth;
	auto norHeight = (double)height / (double)imageHeight;


	auto textStr = classId + " " +
		std::to_string(norCenterX) + " " + std::to_string(norCenterY) + " "
		+ std::to_string(norWidth) + " " + std::to_string(norHeight);

	//是Segment附加mask
	if (checkType == 1)
	{
		using Point = std::pair<double, double>;
		std::vector< Point> points;
		points.reserve(31);

		double angleStep = 2 * M_PI / 30;

		//算出半径
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
	auto tranPath = SaveDataLabelTranPath(learnInfoSign).toStdString() + "\\" + dateTimeStr + ".txt";
	MakeDir(QString::fromStdString(tranPath));
	std::ofstream tranOfs(tranPath);
	tranOfs << textStr;
	tranOfs.close();

	auto valPath = SaveDataLabelValPath(learnInfoSign).toStdString() + "\\" + dateTimeStr + ".txt";
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

QString AiLearnTools::SaveDataLabelTranPath(std::string learnInfoSign)
{
	return	 QString::fromStdString(PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataTranLabel);
}

QString AiLearnTools::SaveDataLabelValPath(std::string learnInfoSign)
{
	return	 QString::fromStdString(PathGlobalStruct::AiLearnData + "\\" + learnInfoSign + "\\" + PathGlobalStruct::AiLearnDataValLabel);
}

void AiLearnTools::CopyDirectory(const QString& srcPath, const QString& dstPath)
{
	QDir srcDir(srcPath);

	QDir dstDir(dstPath);

	// 遍历所有文件和子目录（排除 . 和 ..）
	const QFileInfoList entries = srcDir.entryInfoList(
		QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot
	);

	for (const QFileInfo& entry : entries) {
		const QString srcItemPath = entry.absoluteFilePath();
		const QString dstItemPath = dstDir.absoluteFilePath(entry.fileName());

		if (entry.isDir()) {
			// 递归复制子目录
			CopyDirectory(srcItemPath, dstItemPath);
		}
		else if (entry.isFile()) {
			// 处理文件覆盖
			if (QFile::exists(dstItemPath)) {
				QFile::remove(dstItemPath);
			}
			// 复制文件
			if (!QFile::copy(srcItemPath, dstItemPath)) {
				qWarning() << "Failed to copy file:" << srcItemPath << "to" << dstItemPath;
				throw "AiLearnTools复制文件出错!";
			}
		}
	}
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

QImage AiLearnTools::cvMat2QImage(const cv::Mat& mat) {
	// 1. 检查输入有效性
	if (mat.empty()) {
		qWarning("cvMat2QImage: Input cv::Mat is empty!");
		return QImage();
	}

	// 2. 深拷贝非连续内存（避免数据失效）
	cv::Mat localMat;
	if (!mat.isContinuous()) {
		localMat = mat.clone();  // 强制连续存储
	}
	else {
		localMat = mat;          // 直接引用（但需确保外部数据生命周期）
	}

	// 3. 根据通道数转换
	switch (localMat.type()) {
		// 8-bit 1 channel (grayscale)
		// 
	// 处理灰度图
	case CV_8UC1: {
		QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_Grayscale8);
		return image;
	}
				// 处理彩色图
	case CV_8UC3: {
		// 注意：OpenCV 的 BGR 转 Qt 的 RGB
		QImage image(mat.data, mat.cols, mat.rows, static_cast<int>(mat.step), QImage::Format_BGR888);
		return image.rgbSwapped();
	}
				// 处理带有 Alpha 通道的图
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
