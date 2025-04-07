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
    double t = (double)cv::getTickCount();

    // Process the frame
    _modelEnginePtr->ProcessMask(frame, resultImage, maskImage, vecRecogResult);

    // Calculate elapsed time
    t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
   //LOG () "ProcessMask execution time: " << t*1000 << " seconds";  
   return resultImage.clone();
}

cv::Mat ImageProcessor::processElimination(cv::Mat& frame)
{
    // ģ���޳��㷨����
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
    while (!QThread::currentThread()->isInterruptionRequested()) {
        cv::Mat frame;
        {
            QMutexLocker locker(&mutex);
            if (queue.isEmpty()) {
                condition.wait(&mutex);
                if (QThread::currentThread()->isInterruptionRequested()) {
                    break;
                }
            }
            frame = queue.dequeue();
        }

        // AIʶ����
        cv::Mat result = processAI(frame);

        // �޳��㷨����
        result = processElimination(result);

        // ת��ΪQImage
        QImage image = cvMatToQImage(result);

        // ��ʾ������
        emit imageReady(image);
        count++;
        LOG() "index:"<< workindex<<"count" << count;

    }
}

void ImageProcessingModule::BuildModule()
{
    for (int i = 0; i < numConsumers; ++i) {
        static size_t workIndexCount = 0;
        ImageProcessor* processor = new ImageProcessor(queue, mutex, condition, workIndexCount, this);
        workIndexCount++;
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
    // ֪ͨ�����߳��˳�
    for (auto processor : processors) {
        processor->requestInterruption();
    }

    // �������еȴ����߳�
    {
        QMutexLocker locker(&mutex);
        condition.wakeAll();
    }

    // �ȴ������߳��˳�
    for (auto processor : processors) {
        if (processor->isRunning()) {
            processor->wait(1000); // ʹ�ó�ʱ���ƣ��ȴ�1��
        }
        delete processor;
    }
}

void ImageProcessingModule::onFrameCaptured(cv::Mat frame,float location)
{
    QMutexLocker locker(&mutex);
    queue.enqueue(frame);
    condition.wakeOne();
}
