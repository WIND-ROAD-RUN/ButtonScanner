#pragma once
#include <QImage>
#include"opencv2/opencv.hpp"
#include<QString>

QImage cvMatToQImage(const cv::Mat& mat);

QPixmap cvMatToQPixmap(const cv::Mat& mat);


inline struct GlobalPath
{
public:
	QString projectHome = R"(D:\zfkjData\ButtonScanner\)";
public:
	QString modelStorageManagerRootPath = projectHome+  R"(ModelStorage\)";
public:
	QString configRootPath = projectHome + R"(config\)";
public:
	QString modelRootPath= projectHome + R"(model\)";
	QString nameFileName = R"(index.names)";
	QString engineFileName = R"(model.engine)";
	QString onnxFileName = R"(modelOnnx.onnx)";
public:
	QString imageSaveRootPath= projectHome + R"(SavedImages\)";
}globalPath;
