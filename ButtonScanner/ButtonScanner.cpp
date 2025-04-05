#include "stdafx.h"

#include "ButtonScanner.h"
#include"DlgProductSet.h"
#include"DlgProduceLineSet.h"

#include"rqw_CameraObjectThread.hpp"
#include"hoec_CameraException.hpp"

#include"GlobalStruct.h"

#include<qdebug>
#include<QtConcurrent>
ButtonScanner::ButtonScanner(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ButtonScannerClass())
{
    ui->setupUi(this);

    build_ui();
    build_connect();
    build_Motion();

    build_camera();
    start_monitor();
}

ButtonScanner::~ButtonScanner()
{
    delete ui;
}

void ButtonScanner::set_radioButton()
{
    ui->rbtn_debug->setAutoExclusive(false);
    ui->rbtn_defect->setAutoExclusive(false);
    ui->rbtn_downLight->setAutoExclusive(false);
    ui->rbtn_ForAndAgainst->setAutoExclusive(false);
    ui->rbtn_removeFunc->setAutoExclusive(false);
    ui->rbtn_sideLight->setAutoExclusive(false);
    ui->rbtn_takePicture->setAutoExclusive(false);
    ui->rbtn_upLight->setAutoExclusive(false);
}

void ButtonScanner::build_ui()
{
    //Set RadioButton ,make sure these can be checked at the same time
    set_radioButton();
}

void ButtonScanner::build_connect()
{
    QObject::connect(ui->pbtn_exit, &QPushButton::clicked, this, &ButtonScanner::pbtn_exit_clicked);

    QObject::connect(ui->pbtn_set, &QPushButton::clicked, this, &ButtonScanner::pbtn_set_clicked);

    QObject::connect(ui->pbtn_newProduction, &QPushButton::clicked, this, &ButtonScanner::pbtn_newProduction_clicked);
}

void ButtonScanner::build_camera()
{
    auto isTargetCamera = [](const QString& cameraIndex, const QString& targetName) {
        QRegularExpression regex(R"((\d+)\.(\d+)\.(\d+)\.(\d+))");
        QRegularExpressionMatch match = regex.match(targetName);

        if (match.hasMatch()) {
            auto matchString = match.captured(3);

            return cameraIndex == matchString;
        }

        return false;
        };


    auto cameraMetaDataCheck =
        [isTargetCamera](const QString& cameraIndex, const QVector<rw::rqw::CameraMetaData>& cameraInfo) {
        for (const auto& cameraMetaData : cameraInfo) {
            if (isTargetCamera(cameraIndex, cameraMetaData.ip)) {
                return cameraMetaData;
            }
        }
        rw::rqw::CameraMetaData error;
        error.ip = "0";
        return error;
        };

    auto cameraList = rw::rqw::CheckCameraList();

    {
        QString cameraIp1 = "11";
        auto cameraMetaData1 = cameraMetaDataCheck(cameraIp1, cameraList);

        if (cameraMetaData1.ip != "0") {
            try
            {
                _camera1 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
                _camera1->initCamera(cameraMetaData1, rw::rqw::CameraObjectTrigger::Hardware);
                QObject::connect(_camera1.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera1Display, Qt::DirectConnection);
            }
            catch (const std::exception&)
            {
                qDebug() << "Camera 1 initialization failed.";
            }

        }
    }



    {
        QString cameraIp2 = "12";
        auto cameraMetaData2 = cameraMetaDataCheck(cameraIp2, cameraList);

        if (cameraMetaData2.ip != "0") {
            try
            {
                _camera2 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
                _camera2->initCamera(cameraMetaData2, rw::rqw::CameraObjectTrigger::Hardware);
                QObject::connect(_camera2.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera2Display, Qt::DirectConnection);
            }
            catch (const std::exception&)
            {
                qDebug() << "Camera 2 initialization failed.";
            }

        }
    }

    {
        QString cameraIp3 = "13";
        auto cameraMetaData3 = cameraMetaDataCheck(cameraIp3, cameraList);
        if (cameraMetaData3.ip != "0") {
            try
            {
                _camera3 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
                _camera3->initCamera(cameraMetaData3, rw::rqw::CameraObjectTrigger::Hardware);
                QObject::connect(_camera3.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera3Display, Qt::DirectConnection);
            }
            catch (const std::exception&)
            {
                qDebug() << "Camera 3 initialization failed.";
            }
        }
    }
    {
        QString cameraIp4 = "14";
        auto cameraMetaData4 = cameraMetaDataCheck(cameraIp4, cameraList);
        if (cameraMetaData4.ip != "0") {
            try
            {
                _camera4 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
                _camera4->initCamera(cameraMetaData4, rw::rqw::CameraObjectTrigger::Hardware);
                QObject::connect(_camera4.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera4Display, Qt::DirectConnection);
            }
            catch (const std::exception&)
            {
                qDebug() << "Camera 4 initialization failed.";
            }
        }
    }





}

void ButtonScanner::start_monitor()
{
    if (_camera1)
    {
        try
        {
            _camera1->startMonitor();
        }
        catch (rw::hoec::CameraMonitorError& e)
        {
            qDebug() << "Camera 1 startMonitor failed: " << e.what();
        }

    }
    if (_camera2)
    {
        try
        {
            _camera2->startMonitor();
        }
        catch (rw::hoec::CameraMonitorError& e)
        {
            qDebug() << "Camera 2 startMonitor failed: " << e.what();
        }
    }
    if (_camera3)
    {
        try
        {
            _camera3->startMonitor();
        }
        catch (const rw::hoec::CameraMonitorError& e)
        {
            qDebug() << "Camera 3 startMonitor failed: " << e.what();
        }
    }
    if (_camera4)
    {
        try
        {
            _camera4->startMonitor();
        }
        catch (const rw::hoec::CameraMonitorError& e)
        {
            qDebug() << "Camera 4 startMonitor failed: " << e.what();
        }
    }
}
//初始化运动控制卡
void ButtonScanner::build_Motion()
{
    //这里获取全局变量
    auto& globalStruct = GlobalStruct::getInstance();

    //获取Zmotion
    auto& motionPtr = globalStruct.motionPtr;

    //下面通过motionPtr进行操作
}

QImage ButtonScanner::cvMatToQImage(const cv::Mat& mat)
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
        qDebug() << "Unsupported image format";
        return QImage();
    }

}



#include <future>

// Define the longRunningTask function
cv::Mat longRunningTask(const cv::Mat& frame) {
    // Simulate a long-running task
    cv::Mat result = frame.clone();
    // Perform some processing on the frame
    // ...
    return result;
}

void ButtonScanner::_camera1Display(cv::Mat frame)
{
    static auto lastCallTime = std::chrono::steady_clock::now();
    auto currentCallTime = std::chrono::steady_clock::now();
    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentCallTime - lastCallTime).count();
    lastCallTime = currentCallTime;

    qDebug() << "Time since last camera 1 call: " << timeDiff << " ms";

    static size_t frameCount = 0;
    qDebug() << "Camera 1 frame count: " << ++frameCount;

    auto& globalStruct = GlobalStruct::getInstance();
    auto& modelEngine = globalStruct.modelEnginePtr1;

    // 使用std::async执行耗时任务
    std::future<cv::Mat> resultFuture = std::async(std::launch::async, longRunningTask, frame);

    // 获取任务结果（阻塞直到任务完成）
    cv::Mat result = resultFuture.get();

    qDebug() << "Camera 1 frame captured.";

    // 使用QMetaObject::invokeMethod在主线程中更新UI
    QMetaObject::invokeMethod(this, [this, result]() {
        QImage image = cvMatToQImage(result);
        if (!image.isNull()) {
            ui->label_imgDisplay->setPixmap(QPixmap::fromImage(image));
        }
        else {
            qDebug() << "Failed to convert cv::Mat to QImage in label_imgDisplay slots";
        }
    }, Qt::QueuedConnection);
}
void ButtonScanner::_camera2Display(cv::Mat frame)
{
    static auto lastCallTime = std::chrono::steady_clock::now();
    auto currentCallTime = std::chrono::steady_clock::now();
    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentCallTime - lastCallTime).count();
    lastCallTime = currentCallTime;

    qDebug() << "Time since last camera 2 call: " << timeDiff << " ms";

    static size_t frameCount = 0;
    qDebug() << "Camera 2 frame count: " << ++frameCount;

    auto& globalStruct = GlobalStruct::getInstance();
    auto& modelEngine = globalStruct.modelEnginePtr2;

    // 使用std::async执行耗时任务
    std::future<cv::Mat> resultFuture = std::async(std::launch::async, longRunningTask, frame);

    // 获取任务结果（阻塞直到任务完成）
    cv::Mat result = resultFuture.get();

    qDebug() << "Camera 1 frame captured.";

    // 使用QMetaObject::invokeMethod在主线程中更新UI
    QMetaObject::invokeMethod(this, [this, result]() {
        QImage image = cvMatToQImage(result);
        if (!image.isNull()) {
            ui->label_imgDisplay_2->setPixmap(QPixmap::fromImage(image));
        }
        else {
            qDebug() << "Failed to convert cv::Mat to QImage in label_imgDisplay slots";
        }
        }, Qt::QueuedConnection);
}
void ButtonScanner::_camera3Display(cv::Mat frame)
{
    static auto lastCallTime = std::chrono::steady_clock::now();
    auto currentCallTime = std::chrono::steady_clock::now();
    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentCallTime - lastCallTime).count();
    lastCallTime = currentCallTime;

    qDebug() << "Time since last camera 3 call: " << timeDiff << " ms";

    static size_t frameCount = 0;
    qDebug() << "Camera 3 frame count: " << ++frameCount;

    auto& globalStruct = GlobalStruct::getInstance();
    auto& modelEngine = globalStruct.modelEnginePtr3;

    // 使用std::async执行耗时任务
    std::future<cv::Mat> resultFuture = std::async(std::launch::async, longRunningTask, frame);

    // 获取任务结果（阻塞直到任务完成）
    cv::Mat result = resultFuture.get();

    qDebug() << "Camera 3 frame captured.";

    // 使用QMetaObject::invokeMethod在主线程中更新UI
    QMetaObject::invokeMethod(this, [this, result]() {
        QImage image = cvMatToQImage(result);
        if (!image.isNull()) {
            ui->label_imgDisplay_3->setPixmap(QPixmap::fromImage(image));
        }
        else {
            qDebug() << "Failed to convert cv::Mat to QImage in label_imgDisplay slots";
        }
        }, Qt::QueuedConnection);
}
void ButtonScanner::_camera4Display(cv::Mat frame)
{
    static auto lastCallTime = std::chrono::steady_clock::now();
    auto currentCallTime = std::chrono::steady_clock::now();
    auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(currentCallTime - lastCallTime).count();
    lastCallTime = currentCallTime;

    qDebug() << "Time since last camera 1 call: " << timeDiff << " ms";

    static size_t frameCount = 0;
    qDebug() << "Camera 4 frame count: " << ++frameCount;

    auto& globalStruct = GlobalStruct::getInstance();
    auto& modelEngine = globalStruct.modelEnginePtr4;

    // 使用std::async执行耗时任务
    std::future<cv::Mat> resultFuture = std::async(std::launch::async, longRunningTask, frame);

    // 获取任务结果（阻塞直到任务完成）
    cv::Mat result = resultFuture.get();

    qDebug() << "Camera 4 frame captured.";

    // 使用QMetaObject::invokeMethod在主线程中更新UI
    QMetaObject::invokeMethod(this, [this, result]() {
        QImage image = cvMatToQImage(result);
        if (!image.isNull()) {
            ui->label_imgDisplay_4->setPixmap(QPixmap::fromImage(image));
        }
        else {
            qDebug() << "Failed to convert cv::Mat to QImage in label_imgDisplay slots";
        }
        }, Qt::QueuedConnection);
}
void ButtonScanner::pbtn_set_clicked()
{
    DlgProduceLineSet dlgProduceLineSet;
    dlgProduceLineSet.exec();
}

void ButtonScanner::pbtn_newProduction_clicked()
{
    DlgProductSet dlgProductSet;
    dlgProductSet.exec();
}

void ButtonScanner::pbtn_exit_clicked()
{
    //TODO: question messagebox
    this->close();
}
