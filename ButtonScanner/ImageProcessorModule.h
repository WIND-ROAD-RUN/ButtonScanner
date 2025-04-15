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
#include"ime_modelOnnxRuntime.h"

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

    static void drawTextOnImage(QImage& image, const QVector<QString>& texts, const QVector<Color>& colorList = { Color::Red,Color::Green }, double proportion = 0.8);

    static void drawCirclesOnImage(cv::Mat& image, const std::vector<rw::ime::ProcessRectanglesResultST>& rectangles);
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
    void imageReady(QPixmap image);

private:
    std::unique_ptr<rw::ime::ModelEngineST> _modelEnginePtr;

    std::unique_ptr<rw::ime::ModelEngineOO> _modelEnginePtrOnnx;

public:
    void buildModelEngine(const QString& enginePath, const QString& namePath);

    void buildModelEngineOnnx(const QString& enginePath, const QString& namePath);

private:
    cv::Mat processAI(MatInfo& frame, QVector<QString>& errorInfo, std::vector<rw::ime::ProcessRectanglesResultST>& vecRecogResult);
    void eliminationLogic(MatInfo& frame, cv::Mat& resultImage, QVector<QString>& errorInfo, std::vector<rw::ime::ProcessRectanglesResultST>& processRectanglesResult);

    QImage cvMatToQImage(const cv::Mat& mat);

    void drawErrorLocate(QImage& image, std::vector<rw::ime::ProcessRectanglesResultST>& vecRecogResult);

    QQueue<MatInfo>& _queue;
    QMutex& _mutex;
    QWaitCondition& _condition;
    int _workIndex;
public:
    int imageProcessingModuleIndex;
};

class ImageProcessingModule : public QObject {
    Q_OBJECT
public:
    QString modelEnginePath;
    QString modelNamePath;
    QString modelEnginePathOnnx;
public:
    void BuildModule();
public:
    ImageProcessingModule(int numConsumers, QObject* parent = nullptr);

    ~ImageProcessingModule();

public slots:
    void onFrameCaptured(cv::Mat frame, float location, size_t index);

signals:
    void imageReady(QPixmap image);
public:
    std::vector<ImageProcessor*> getProcessors() const {
        return _processors;
    }

private:
    QQueue<MatInfo> _queue;
    QMutex _mutex;
    QWaitCondition _condition;
    std::vector<ImageProcessor*> _processors;
    int _numConsumers;
public:
    size_t index;
};
