#pragma once

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QPainter>
#include <QFont>
#include <vector>
#include <string>

#include"ime_ModelEngine.h"

struct ImagePainter
{
    enum Color {
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        CYAN,
        MAGENTA,
        BLACK
    };

    static QColor ColorToQColor(Color c);

    static void drawTextOnImage(QImage& image, const QVector<QString>& texts, const QVector<Color>& colorList = { Color ::RED,Color::GREEN}, double proportion = 0.3);
};


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
    void processResult(bool isOk,float location);

private:
    std::unique_ptr<rw::ime::ModelEngine> _modelEnginePtr;
public:
    void buildModelEngine(const QString& enginePath, const QString& namePath);

private:
    cv::Mat processAI(MatInfo& frame,QVector<QString> & errorInfo);

    QImage cvMatToQImage(const cv::Mat& mat,const QVector<QString>& errorInfo);

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
    void onProcessResult(bool isOk, float location);

signals:
    void imageReady(const QImage& image);
    void processResult(bool isOk, float location);

private:
    QQueue<MatInfo> queue;
    QMutex mutex;
    QWaitCondition condition;
    std::vector<ImageProcessor*> processors;
    int numConsumers;
};

