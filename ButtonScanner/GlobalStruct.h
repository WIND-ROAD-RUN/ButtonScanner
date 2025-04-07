#pragma once

#include<memory>

#include"ImageProcessorModule.h"

#include"scc_Motion.h"
#include"ime_ModelEngine.h"
#include"rqw_CameraObjectThread.hpp"
#include"cdm_ButtonScannerMainWindow.h"
#include"cdm_ButtonScannerDlgProductSet.h"
#include"oso_StorageContext.hpp"
#include<QString>
#include <cdm_ButtonScannerProduceLineSet.h>

namespace zwy {
    namespace scc {
        class Motion;
    }
}

class GlobalStruct
    :public QObject
{
    Q_OBJECT
public:
    void buildConfigManager(rw::oso::StorageType type);
    void ReadConfig();
    void saveConfig();
    std::unique_ptr<rw::oso::StorageContext> _StoreContext{ nullptr };
public:
    QString mainwindowFilePath;
	QString dlgProduceLineSetFilePath;
    QString dlgProductSetFilePath;
    rw::cdm::ButtonScannerMainWindow mainWindowConfig{};
	rw::cdm::ButtonScannerProduceLineSet dlgProduceLineSetConfig{};
    rw::cdm::ButtonScannerDlgProductSet dlgProductSetConfig{};
public:
    QString cameraIp1{ "11" };
    QString cameraIp2{ "12" };
    QString cameraIp3{ "13" };
    QString cameraIp4{ "14" };
public:
    QString enginePath{ R"(C:\Users\34615\Desktop\best.engine)" };
    QString namePath{ R"(C:\Users\34615\Desktop\index.names)" };
public:

    void buildCamera();
    void startMonitor();
    void destroyCamera();
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera1{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera2{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera3{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera4{ nullptr };

public:
    //调用前确保模型文件存在且以设置
    void buildImageProcessingModule(size_t num);
    void destroyImageProcessingModule();

    std::unique_ptr<ImageProcessingModule> _imageProcessingModule1{ nullptr };
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule2{ nullptr };
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule3{ nullptr };
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule4{ nullptr };

public:
    void buildMotion();

    void destroyMotion();

    std::unique_ptr<zwy::scc::Motion> _motionPtr;

public:
    static GlobalStruct& getInstance()
    {
        static GlobalStruct instance;
        return instance;
    }

    GlobalStruct(const GlobalStruct&) = delete;
    GlobalStruct& operator=(const GlobalStruct&) = delete;

private:
    GlobalStruct();
    ~GlobalStruct() = default;
};