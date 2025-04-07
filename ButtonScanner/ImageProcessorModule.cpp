#include"stdafx.h"

#include"ImageProcessorModule.h"

void ImageProcessor::buildModelEngine(const QString& enginePath, const QString& namePath)
{
    _modelEnginePtr = std::make_unique<rw::ime::ModelEngine>(enginePath.toStdString(),namePath.toStdString());
}

cv::Mat ImageProcessor::processAI(cv::Mat& frame)
{
    cv::Mat resultImage;
    cv::Mat maskImage = cv::Mat::zeros(frame.size(), CV_8UC1);
    std::vector<rw::ime::ProcessRectanglesResult> vecRecogResult;
    _modelEnginePtr->ProcessMask(frame,resultImage, maskImage, vecRecogResult);
    return resultImage.clone();
}

cv::Mat ImageProcessor::processElimination(cv::Mat& frame)
{
    // 模拟剔除算法处理
    //QThread::msleep(10);
    return frame;
}

QImage ImageProcessor::cvMatToQImage(const cv::Mat& mat)
{
    if (mat.type() == CV_8UC1) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_Grayscale8);
    }
    else if (mat.type() == CV_8UC3) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_RGB888).rgbSwapped();
    }
    else if (mat.type() == CV_8UC4) {
        return QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_RGBA8888);
    }
    else {
        return QImage();
    }
}

ImageProcessor::ImageProcessor(QQueue<cv::Mat>& queue, QMutex& mutex, QWaitCondition& condition, int workindex, QObject* parent)
    : QThread(parent), queue(queue), mutex(mutex), condition(condition), workindex(workindex) {
}

void ImageProcessor::run()
{
    while (true) {
        cv::Mat frame;
        {
            QMutexLocker locker(&mutex);
            if (queue.isEmpty()) {
                condition.wait(&mutex);
            }
            frame = queue.dequeue();
        }

        // AI识别处理
        cv::Mat result = processAI(frame);

        // 剔除算法处理
        result = processElimination(result);

        // 转换为QImage
        QImage image = cvMatToQImage(result);

        // 显示到界面
        emit imageReady(image);

        // 模拟其他操作
        QThread::msleep(100);
    }
}

void ImageProcessingModule::BuildModule()
{
    for (int i = 0; i < numConsumers; ++i) {
        ImageProcessor* processor = new ImageProcessor(queue, mutex, condition, i, this);
        processor->buildModelEngine(modelEnginePath, modelNamePath);
        connect(processor, &ImageProcessor::imageReady, this, &ImageProcessingModule::imageReady, Qt::QueuedConnection);
        processors.push_back(processor);
        processor->start();
    }
}

ImageProcessingModule::ImageProcessingModule(int numConsumers, QObject* parent)
    : QObject(parent), numConsumers(numConsumers) {
    
}

ImageProcessingModule::~ImageProcessingModule()
{
    for (auto processor : processors) {
        processor->quit();
        processor->wait();
        delete processor;
    }
}

void ImageProcessingModule::onFrameCaptured(cv::Mat frame)
{
    QMutexLocker locker(&mutex);
    queue.enqueue(frame);
    condition.wakeOne();
}
