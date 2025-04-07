#pragma once

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>
#include <opencv2/opencv.hpp>


class ImageProcessor : public QThread {
    Q_OBJECT

public:
    ImageProcessor(QQueue<cv::Mat>& queue,
        QMutex& mutex,
        QWaitCondition& condition,
        int workindex,
        QObject* parent = nullptr);

protected:
    void run() override; 

signals:
    void imageReady(const QImage& image);

private:
    cv::Mat processAI(const cv::Mat& frame);

    cv::Mat processElimination(const cv::Mat& frame);

    QImage cvMatToQImage(const cv::Mat& mat);

    QQueue<cv::Mat>& queue;
    QMutex& mutex;
    QWaitCondition& condition;
    int workindex;
};

class ImageProcessingModule : public QObject {
    Q_OBJECT

public:
    ImageProcessingModule(int numConsumers, QObject* parent = nullptr);
       
    ~ImageProcessingModule();

public slots :
    void onFrameCaptured(cv::Mat frame);

signals:
    void imageReady(const QImage& image);

private:
    QQueue<cv::Mat> queue;
    QMutex mutex;
    QWaitCondition condition;
    std::vector<ImageProcessor*> processors;
    int numConsumers;
};

