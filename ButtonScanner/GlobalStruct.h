#pragma once

#include<memory>

#include"ImageProcessorModule.h"

#include"scc_Motion.h"
#include"ime_ModelEngine.h"
#include"rqw_CameraObjectThread.hpp"

#include<QString>

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
    QString cameraIp1{ "11" };
    QString cameraIp2{ "12" };
    QString cameraIp3{ "13" };
    QString cameraIp4{ "14" };
public:
    QString enginePath{ R"(C:\Users\34615\Desktop\best.engine)" };
    QString namePath{ R"(C:\Users\34615\Desktop\index.names)" };
public:
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera1{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera2{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera3{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera4{ nullptr };

public:
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule1{ nullptr };
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule2{ nullptr };
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule3{ nullptr };
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule4{ nullptr };

public:
    void buildImageProcessingModule(size_t num);

    void buildCamera();
    void startMonitor();

    void buildModelEngine();
    void buildMotion();

public:
    std::unique_ptr<zwy::scc::Motion> motionPtr;
public:
    std::unique_ptr<rw::ime::ModelEngine> modelEnginePtr1;
    std::unique_ptr<rw::ime::ModelEngine> modelEnginePtr2;
    std::unique_ptr<rw::ime::ModelEngine> modelEnginePtr3;
    std::unique_ptr<rw::ime::ModelEngine> modelEnginePtr4;

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