#pragma once
#include <QImage>
#include"opencv2/opencv.hpp"

QImage cvMatToQImage(const cv::Mat& mat);

QPixmap cvMatToQPixmap(const cv::Mat & mat);