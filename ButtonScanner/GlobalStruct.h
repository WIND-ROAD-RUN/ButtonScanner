#pragma once

#include<memory>

#include"ImageProcessorModule.h"

#include"scc_Motion.h"
#include"ime_ModelEngine.h"
#include"rqw_CameraObjectThread.hpp"
#include"cdm_ButtonScannerMainWindow.h"
#include"cdm_ButtonScannerDlgProductSet.h"
#include"cdm_ButtonScannerDlgExposureTimeSet.h"
#include"dsl_PriorityQueue.hpp"
#include"oso_StorageContext.hpp"
#include<QString>
#include <cdm_ButtonScannerProduceLineSet.h>
#include<atomic>

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
public:
    void ReadConfig();
    void ReadMainWindowConfig();
    void ReadDlgProduceLineSetConfig();
    void ReadDlgProductSetConfig();
    void ReadDlgExposureTimeSetConfig();
public:
    void saveConfig();
    void saveMainWindowConfig();
    void saveDlgProduceLineSetConfig();
    void saveDlgProductSetConfig();
    void saveDlgExposureTimeSetConfig();
    std::unique_ptr<rw::oso::StorageContext> storeContext{ nullptr };
public:
    QString mainWindowFilePath;
    QString dlgProduceLineSetFilePath;
    QString dlgProductSetFilePath;
    QString dlgExposureTimeSetFilePath;
    rw::cdm::ButtonScannerMainWindow mainWindowConfig{};
    rw::cdm::ButtonScannerProduceLineSet dlgProduceLineSetConfig{};
    rw::cdm::ButtonScannerDlgProductSet dlgProductSetConfig{};
    rw::cdm::ButtonScannerDlgExposureTimeSet dlgExposureTimeSetConfig{};
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
    std::unique_ptr<rw::rqw::CameraPassiveThread> camera1{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> camera2{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> camera3{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> camera4{ nullptr };

public:
    //调用前确保模型文件存在且以设置
    void buildImageProcessingModule(size_t num);
    void destroyImageProcessingModule();

    std::unique_ptr<ImageProcessingModule> imageProcessingModule1{ nullptr };
    std::unique_ptr<ImageProcessingModule> imageProcessingModule2{ nullptr };
    std::unique_ptr<ImageProcessingModule> imageProcessingModule3{ nullptr };
    std::unique_ptr<ImageProcessingModule> imageProcessingModule4{ nullptr };
public:
    static GlobalStruct& getInstance()
    {
        static GlobalStruct instance;
        return instance;
    }

    GlobalStruct(const GlobalStruct&) = delete;
    GlobalStruct& operator=(const GlobalStruct&) = delete;
public:
    rw::dsl::ThreadSafeDHeap<float, float> productPriorityQueue1;
    rw::dsl::ThreadSafeDHeap<float, float> productPriorityQueue2;
    rw::dsl::ThreadSafeDHeap<float, float> productPriorityQueue3;
    rw::dsl::ThreadSafeDHeap<float, float> productPriorityQueue4;
private:
    GlobalStruct();
    ~GlobalStruct() = default;
private slots:
    void onCamera1ImageReady(bool isOk, float location);
    void onCamera2ImageReady(bool isOk, float location);
    void onCamera3ImageReady(bool isOk, float location);
    void onCamera4ImageReady(bool isOk, float location);
};