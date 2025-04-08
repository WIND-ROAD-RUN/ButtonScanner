#pragma once

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>
#include <opencv2/opencv.hpp>

#include"ime_ModelEngine.h"


struct MatInfo {
    cv::Mat image;
    float loaction;
    size_t index;
};

class ImageProcessor : public QThread {
    Q_OBJECT

public:
    ImageProcessor(QQueue<MatInfo>& queue,
        QMutex& mutex,
        QWaitCondition& condition,
        int workindex,
        QObject* parent = nullptr);
    int count;

protected:
    void run() override; 

signals:
    void imageReady(const QImage& image);

private:
    std::unique_ptr<rw::ime::ModelEngine> _modelEnginePtr;
public:
    void buildModelEngine(const QString& enginePath, const QString& namePath);

private:
    cv::Mat processAI(MatInfo& frame);

    QImage cvMatToQImage(const cv::Mat& mat);

    QQueue<MatInfo>& queue;
    QMutex& mutex;
    QWaitCondition& condition;
    int workindex;
};

class ImageProcessingModule : public QObject {
    Q_OBJECT
public:
    QString modelEnginePath;
    QString modelNamePath;
public:
    void BuildModule();
public:
    ImageProcessingModule(int numConsumers, QObject* parent = nullptr);
       
    ~ImageProcessingModule();

public slots :
    void onFrameCaptured(cv::Mat frame,float location, size_t index);

signals:
    void imageReady(const QImage& image);

private:
    QQueue<MatInfo> queue;
    QMutex mutex;
    QWaitCondition condition;
    std::vector<ImageProcessor*> processors;
    int numConsumers;
};

