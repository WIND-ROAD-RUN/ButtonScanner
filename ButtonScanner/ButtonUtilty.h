#pragma once
#include <QImage>
#include"opencv2/opencv.hpp"
#include<QString>

QImage cvMatToQImage(const cv::Mat& mat);

QPixmap cvMatToQPixmap(const cv::Mat& mat);


inline struct GlobalPath
{
	QString moduleStorageManagerRootPath = R"(D:\zfkjData\ButtonScanner\ModelStorageManager\)";
	
}globalPath;
