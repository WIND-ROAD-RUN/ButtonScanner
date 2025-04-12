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
#include"MonitorCameraAndCardStateThread.h"
#include"dsl_ThreadSafeMinHeap.h"

#include<QString>

#include<atomic>

namespace zwy {
    namespace scc {
        class Motion;
    }
}

class GlobalStructThread
    :public QObject
{
    Q_OBJECT
public:
    std::unique_ptr<StatisticalInfoComputingThread> statisticalInfoComputingThread{ nullptr };
    std::unique_ptr<MonitorCameraAndCardStateThread> monitorCameraAndCardStateThread{ nullptr };
public:
    void buildDetachThread();
    void destroyDetachThread();
public:
    static GlobalStructThread& getInstance()
    {
        static GlobalStructThread instance;
        return instance;
    }

    GlobalStructThread(const GlobalStructThread&) = delete;
    GlobalStructThread& operator=(const GlobalStructThread&) = delete;

private:
    GlobalStructThread();
    ~GlobalStructThread() = default;

};


class GlobalStructData
    :public QObject
{
    Q_OBJECT
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
    std::atomic_bool isDebugMode{ false };
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
    void destroyCamera1();
    void destroyCamera2();
    void destroyCamera3();
    void destroyCamera4();
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
    static GlobalStructData& getInstance()
    {
        static GlobalStructData instance;
        return instance;
    }

    GlobalStructData(const GlobalStructData&) = delete;
    GlobalStructData& operator=(const GlobalStructData&) = delete;
public:
    ThreadSafeMinHeap productPriorityQueue1;
    ThreadSafeMinHeap productPriorityQueue2;
    ThreadSafeMinHeap productPriorityQueue3;
    ThreadSafeMinHeap productPriorityQueue4;
private:
    GlobalStructData();
    ~GlobalStructData() = default;
public slots:
    void onBuildCamera1();
    void onBuildCamera2();
    void onBuildCamera3();
    void onBuildCamera4();

    void onDestroyCamera1();
    void onDestroyCamera2();
    void onDestroyCamera3();
    void onDestroyCamera4();

    void onStartMonitor1();
    void onStartMonitor2();
    void onStartMonitor3();
    void onStartMonitor4();
};