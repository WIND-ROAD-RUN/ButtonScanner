#pragma once

#include<memory>

#include"ImageProcessorModule.h"

#include"scc_Motion.h"
#include"ime_ModelEngine.h"
#include"rqw_CameraObjectThread.hpp"
#include"cdm_ButtonScannerMainWindow.h"
#include"cdm_ButtonScannerDlgProductSet.h"
#include"cdm_ButtonScannerDlgExposureTimeSet.h"
#include "cdm_ButtonScannerProduceLineSet.h"
#include"dsl_PriorityQueue.hpp"
#include"oso_StorageContext.hpp"
#include"rqw_ImageSaveEngine.h"
#include"StatisticalInfoComputingThread.h"

#include<QString>

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
    std::unique_ptr<StatisticalInfoComputingThread> statisticalInfoComputingThread{ nullptr };
    void build_StatisticalInfoComputingThread();
    void destroy_StatisticalInfoComputingThread();
public:
    struct StatisticalInfo
    {
        std::atomic_uint64_t produceCount{ 0 };
        std::atomic_uint64_t wasteCount{ 0 };
        std::atomic<double> productionYield{ 0 };
        std::atomic<double> removeRate{ 0 };
    } statisticalInfo;
public:
    std::atomic_bool isTakePictures{ false };
    std::atomic_bool isOpenRemoveFunc{false};
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

    bool isTargetCamera(const QString& cameraIndex, const QString& targetName);
    rw::rqw::CameraMetaData cameraMetaDataCheck(const QString& cameraIndex, const QVector<rw::rqw::CameraMetaData>& cameraInfo);
    void buildCamera();
    void buildCamera1();
    void buildCamera2();
    void buildCamera3();
    void buildCamera4();


    void startMonitor();
    void destroyCamera();
    std::unique_ptr<rw::rqw::CameraPassiveThread> camera1{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> camera2{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> camera3{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> camera4{ nullptr };

    void setCameraExposureTime(int cameraIndex, size_t exposureTime);

public:
    //调用前确保模型文件存在且以设置
    void buildImageProcessingModule(size_t num);
    void destroyImageProcessingModule();

    std::unique_ptr<ImageProcessingModule> imageProcessingModule1{ nullptr };
    std::unique_ptr<ImageProcessingModule> imageProcessingModule2{ nullptr };
    std::unique_ptr<ImageProcessingModule> imageProcessingModule3{ nullptr };
    std::unique_ptr<ImageProcessingModule> imageProcessingModule4{ nullptr };
public: 
    void buildImageSaveEngine();
    void destroyImageSaveEngine();
    std::unique_ptr<rw::rqw::ImageSaveEngine> imageSaveEngine{ nullptr };
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