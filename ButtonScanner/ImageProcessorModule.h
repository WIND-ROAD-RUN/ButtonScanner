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
        White,
        Red,
        Green,
        Blue,
        Yellow,
        Cyan,
        Magenta,
        Black
    };

    static QColor ColorToQColor(Color c);

    static void drawTextOnImage(QImage& image, const QVector<QString>& texts, const QVector<Color>& colorList = { Color ::Red,Color::Green}, double proportion = 0.6);

    static void drawCirclesOnImage(cv::Mat& image, const std::vector<rw::ime::ProcessRectanglesResult>& rectangles);
};


struct MatInfo {
    cv::Mat image;
    float location;
    size_t index;
};

class ImageProcessor : public QThread {
    Q_OBJECT

public:
    ImageProcessor(QQueue<MatInfo>& queue,
        QMutex& mutex,
        QWaitCondition& condition,
        int workIndex,
        QObject* parent = nullptr);
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
    void eliminationLogic(MatInfo& frame,cv::Mat & resultImage,QVector<QString>& errorInfo, std::vector<rw::ime::ProcessRectanglesResult> & processRectanglesResult);

    QImage cvMatToQImage(const cv::Mat& mat,const QVector<QString>& errorInfo);

    QQueue<MatInfo>& _queue;
    QMutex& _mutex;
    QWaitCondition& _condition;
    int _workIndex;
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
    void processResultModule(bool isOk, float location);

private:
    QQueue<MatInfo> _queue;
    QMutex _mutex;
    QWaitCondition _condition;
    std::vector<ImageProcessor*> _processors;
    int _numConsumers;
};

