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

#include"imeoo_ModelEngineOO.h"
#include"imest_ModelEngineST.h"
#include"imeot_ModelEngineOT.h"

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

    static void drawCirclesOnImage(cv::Mat& image, const std::vector<rw::imeot::ProcessRectanglesResultOT>& rectangles);
};

struct MatInfo {
    cv::Mat image;
    float location;
    size_t index;
};

class ImageProcessor : public QThread {
    Q_OBJECT

private:
    bool _isbad{false};

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
    std::unique_ptr<rw::imeot::ModelEngineOT> _modelEnginePtr;

    std::unique_ptr<rw::imeoo::ModelEngineOO> _modelEnginePtrOnnx;

public:
    void buildModelEngine(const QString& enginePath, const QString& namePath);

    void buildModelEngineOnnx(const QString& enginePath, const QString& namePath);

private:
    bool isInAred(int x);
    std::vector<rw::imeot::ProcessRectanglesResultOT> getDefectInBody(rw::imeot::ProcessRectanglesResultOT body,const std::vector<rw::imeot::ProcessRectanglesResultOT>& vecRecogResult);

private:
    cv::Mat processAI(MatInfo& frame, QVector<QString>& errorInfo, std::vector<rw::imeot::ProcessRectanglesResultOT>& vecRecogResult, std::vector<rw::imeot::ProcessRectanglesResultOT> & vecRecogResultTarget);

    rw::imeot::ProcessRectanglesResultOT getBody(std::vector<rw::imeot::ProcessRectanglesResultOT>& processRectanglesResult,bool &hasBody);

	void eliminationLogic(MatInfo& frame, cv::Mat& resultImage, QVector<QString>& errorInfo, std::vector<rw::imeot::ProcessRectanglesResultOT>& processRectanglesResult, std::vector<rw::imeot::ProcessRectanglesResultOT> & vecRecogResultTarget);

    void drawErrorLocate(QImage& image, std::vector<rw::imeot::ProcessRectanglesResultOT>& vecRecogResult,const QColor& drawColor);

    void drawLine(QImage& image);
    void drawLine_locate(QImage& image,size_t locate);

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

    void imgForDlgNewProduction(cv::Mat mat, size_t index);
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
