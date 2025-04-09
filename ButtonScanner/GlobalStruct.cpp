#include "stdafx.h"

#include "GlobalStruct.h"
#include"hoec_CameraException.hpp"
#include"rqw_CameraObjectThread.hpp"

void GlobalStruct::buildImageProcessingModule(size_t num)
{
    imageProcessingModule1 = std::make_unique<ImageProcessingModule>(num, this);
    imageProcessingModule1->modelEnginePath = enginePath;
    imageProcessingModule1->modelNamePath = namePath;
    imageProcessingModule1->BuildModule();

    imageProcessingModule2 = std::make_unique<ImageProcessingModule>(num, this);
    imageProcessingModule2->modelEnginePath = enginePath;
    imageProcessingModule2->modelNamePath = namePath;
    imageProcessingModule2->BuildModule();

    imageProcessingModule3 = std::make_unique<ImageProcessingModule>(num, this);
    imageProcessingModule3->modelEnginePath = enginePath;
    imageProcessingModule3->modelNamePath = namePath;
    imageProcessingModule3->BuildModule();

    imageProcessingModule4 = std::make_unique<ImageProcessingModule>(num, this);
    imageProcessingModule4->modelEnginePath = enginePath;
    imageProcessingModule4->modelNamePath = namePath;
    imageProcessingModule4->BuildModule();

    //连接相机和图像处理模块
    QObject::connect(camera1.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
        imageProcessingModule1.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);
    QObject::connect(imageProcessingModule1.get(), &ImageProcessingModule::processResultModule,
        this, &GlobalStruct::onCamera1ImageReady, Qt::DirectConnection);

    QObject::connect(camera2.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
        imageProcessingModule2.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);
    QObject::connect(imageProcessingModule2.get(), &ImageProcessingModule::processResultModule,
        this, &GlobalStruct::onCamera2ImageReady, Qt::DirectConnection);

    QObject::connect(camera3.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
        imageProcessingModule3.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);
    QObject::connect(imageProcessingModule3.get(), &ImageProcessingModule::processResultModule,
        this, &GlobalStruct::onCamera3ImageReady, Qt::DirectConnection);

    QObject::connect(camera4.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
        imageProcessingModule4.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);
    QObject::connect(imageProcessingModule4.get(), &ImageProcessingModule::processResultModule,
        this, &GlobalStruct::onCamera4ImageReady, Qt::DirectConnection);
}

void GlobalStruct::buildConfigManager(rw::oso::StorageType type)
{
    storeContext = std::make_unique<rw::oso::StorageContext>(type);
}

void GlobalStruct::ReadConfig()
{
    ReadMainWindowConfig();
    ReadDlgProduceLineSetConfig();
    ReadDlgProductSetConfig();
}

void GlobalStruct::ReadMainWindowConfig()
{
    auto loadMainWindowConfig = storeContext->load(mainWindowFilePath.toStdString());
    if (loadMainWindowConfig) {
        mainWindowConfig = *loadMainWindowConfig;
    }
    else {
        LOG()  "Load main window config failed.";
    }
}

void GlobalStruct::ReadDlgProduceLineSetConfig()
{
    auto loadDlgProduceLineSetConfig = storeContext->load(dlgProduceLineSetFilePath.toStdString());
    if (loadDlgProduceLineSetConfig) {
        dlgProduceLineSetConfig = *loadDlgProduceLineSetConfig;
    }
    else {
        LOG()  "Load main window config failed.";
    }
}

void GlobalStruct::ReadDlgProductSetConfig()
{
    auto loadDlgProductSetConfig = storeContext->load(dlgProductSetFilePath.toStdString());
    if (loadDlgProductSetConfig) {
        dlgProductSetConfig = *loadDlgProductSetConfig;
    }
    else {
        LOG()  "Load main window config failed.";
    }
}

void GlobalStruct::saveConfig()
{
    saveMainWindowConfig();
    saveDlgProduceLineSetConfig();
    saveDlgProductSetConfig();
}

void GlobalStruct::saveMainWindowConfig()
{
    storeContext->save(mainWindowConfig, mainWindowFilePath.toStdString());
}

void GlobalStruct::saveDlgProduceLineSetConfig()
{
    storeContext->save(dlgProduceLineSetConfig, dlgProduceLineSetFilePath.toStdString());
}

void GlobalStruct::saveDlgProductSetConfig()
{
    storeContext->save(dlgProductSetConfig, dlgProductSetFilePath.toStdString());
}

void GlobalStruct::buildCamera()
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
        auto cameraMetaData1 = cameraMetaDataCheck(cameraIp1, cameraList);

        if (cameraMetaData1.ip != "0") {
            try
            {
                camera1 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
                camera1->motionRedix = 2;
                camera1->initCamera(cameraMetaData1, rw::rqw::CameraObjectTrigger::Hardware, 2);
                camera1->cameraIndex = 1;
            }
            catch (const std::exception&)
            {
                LOG()  "Camera 1 initialization failed.";
            }
        }
    }

    {
        auto cameraMetaData2 = cameraMetaDataCheck(cameraIp2, cameraList);

        if (cameraMetaData2.ip != "0") {
            try
            {
                camera2 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
                camera2->motionRedix = 4;
                camera2->initCamera(cameraMetaData2, rw::rqw::CameraObjectTrigger::Hardware, 4);
                camera2->cameraIndex = 2;
            }
            catch (const std::exception&)
            {
                LOG()  "Camera 2 initialization failed.";
            }
        }
    }

    {
        auto cameraMetaData3 = cameraMetaDataCheck(cameraIp3, cameraList);
        if (cameraMetaData3.ip != "0") {
            try
            {
                camera3 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
                camera3->motionRedix = 6;
                camera3->initCamera(cameraMetaData3, rw::rqw::CameraObjectTrigger::Hardware, 6);
                camera3->cameraIndex = 3;
            }
            catch (const std::exception&)
            {
                LOG()  "Camera 3 initialization failed.";
            }
        }
    }
    {
        auto cameraMetaData4 = cameraMetaDataCheck(cameraIp4, cameraList);
        if (cameraMetaData4.ip != "0") {
            try
            {
                camera4 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
                camera4->motionRedix = 8;
                camera4->initCamera(cameraMetaData4, rw::rqw::CameraObjectTrigger::Hardware, 8);
                camera4->cameraIndex = 4;
            }
            catch (const std::exception&)
            {
                LOG()  "Camera 4 initialization failed.";
            }
        }
    }
}

void GlobalStruct::startMonitor()
{
    if (camera1)
    {
        try
        {
            camera1->startMonitor();
        }
        catch (rw::hoec::CameraMonitorError& e)
        {
            LOG()  "Camera 1 startMonitor failed: " << e.what();
        }
    }
    if (camera2)
    {
        try
        {
            camera2->startMonitor();
        }
        catch (rw::hoec::CameraMonitorError& e)
        {
            LOG()  "Camera 2 startMonitor failed: " << e.what();
        }
    }
    if (camera3)
    {
        try
        {
            camera3->startMonitor();
        }
        catch (const rw::hoec::CameraMonitorError& e)
        {
            LOG()  "Camera 3 startMonitor failed: " << e.what();
        }
    }
    if (camera4)
    {
        try
        {
            camera4->startMonitor();
        }
        catch (const rw::hoec::CameraMonitorError& e)
        {
            LOG()  "Camera 4 startMonitor failed: " << e.what();
        }
    }
}

void GlobalStruct::destroyCamera()
{
    camera1.reset();
    camera2.reset();
    camera3.reset();
    camera4.reset();
}

void GlobalStruct::destroyImageProcessingModule()
{
    imageProcessingModule1.reset();
    imageProcessingModule2.reset();
    imageProcessingModule3.reset();
    imageProcessingModule4.reset();
}

GlobalStruct::GlobalStruct()
{
}

void GlobalStruct::onCamera1ImageReady(bool isOk, float location)
{
    LOG()  "Camera 1 image ready: " << isOk << " location: " << location;
    if (!isOk) {
        productPriorityQueue1.insert(location, location);
    }
}

void GlobalStruct::onCamera2ImageReady(bool isOk, float location)
{
    if (!isOk) {
        productPriorityQueue2.insert(location, location);
    }
}

void GlobalStruct::onCamera3ImageReady(bool isOk, float location)
{
    if (!isOk) {
        productPriorityQueue3.insert(location, location);
    }
}

void GlobalStruct::onCamera4ImageReady(bool isOk, float location)
{
    if (!isOk) {
        productPriorityQueue4.insert(location, location);
    }
}