#include "stdafx.h"

#include "ButtonScanner.h"
#include"DlgProductSet.h"
#include"DlgProduceLineSet.h"

#include"rqw_CameraObjectThread.hpp"
#include"hoec_CameraException.hpp"
#include"oso_core.h"
#include"oso_StorageContext.hpp"
#include"cdm_ButtonScannerMainWindow.h"

#include<qdebug>

ButtonScanner::ButtonScanner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ButtonScannerClass())
{
    ui->setupUi(this);

    read_config();

    build_ui();
    build_connect();

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
    QObject::connect(ui->pbtn_exit,&QPushButton::clicked,this, &ButtonScanner::pbtn_exit_clicked);

    QObject::connect(ui->pbtn_set, &QPushButton::clicked, this, &ButtonScanner::pbtn_set_clicked);

    QObject::connect(ui->pbtn_newProduction, &QPushButton::clicked, this, &ButtonScanner::pbtn_newProduction_clicked);
}

void ButtonScanner::read_config()  
{  
  rw::cdm::ButtonScannerMainWindow config;   
  rw::oso::StorageContext storageContext(rw::oso::StorageType::Xml);  

  storageContext.save(config,std::string(R"(C:\Users\34615\Desktop\1\1.xml)"));

  auto loadResult = storageContext.load( std::string(R"(C:\Users\34615\Desktop\1\1.xml)"));

  rw::cdm::ButtonScannerMainWindow cdm(*loadResult);
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
                QObject::connect(_camera2.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera1Display, Qt::DirectConnection);
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
                QObject::connect(_camera3.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera1Display, Qt::DirectConnection);
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
                QObject::connect(_camera4.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera1Display, Qt::DirectConnection);
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

void ButtonScanner::_camera1Display(cv::Mat frame)
{
    qDebug() << "Camera 1 frame captured.";
    QImage image = cvMatToQImage(frame);
    if (!image.isNull()) {
        ui->label_imgDisplay->setPixmap(QPixmap::fromImage(image));
    }
    else {
        qDebug() << "Failed to convert cv::Mat to QImage in label_imgDisplay slots";
    }

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
