#pragma once
#include <QImage>
#include"opencv2/opencv.hpp"
#include<QString>

QImage cvMatToQImage(const cv::Mat& mat);

QPixmap cvMatToQPixmap(const cv::Mat& mat);


inline struct GlobalPath
{
public:
	QString moduleStorageManagerRootPath = R"(D:\zfkjData\ButtonScanner\ModelStorage\)";
	QString configRootPath = R"(D:\zfkjData\ButtonScanner\config\)";
public:
	QString modelRootPath= R"(D:\zfkjData\ButtonScanner\model\)";
	QString nameFileName = R"(index.names)";
	QString engineFileName = R"(model.engine)";
	QString onnxFileName = R"(modelOnnx.onnx)";
public:
	QString imageSaveRootPath= R"(D:\zfkjData\ButtonScanner\SavedImages\)";
}globalPath;
