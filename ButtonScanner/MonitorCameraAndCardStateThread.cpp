#include"stdafx.h"

#include"MonitorCameraAndCardStateThread.h"
#include"GlobalStruct.h"
#include"scc_motion.h"
#include"hoec_Camera.hpp"
#include"rqw_CameraObjectThread.hpp"
#include"rqw_CameraObject.hpp"

MonitorCameraAndCardStateThread::MonitorCameraAndCardStateThread(QObject* parent)
    : QThread(parent), running(false) {
}

MonitorCameraAndCardStateThread::~MonitorCameraAndCardStateThread()
{
    stopThread();
    wait(); 
}

void MonitorCameraAndCardStateThread::startThread()
{
    running = true;
    if (!isRunning()) {
        start(); 
    }
}

void MonitorCameraAndCardStateThread::stopThread()
{
    running = false; 
}

void MonitorCameraAndCardStateThread::run()
{
    while (running) {
        QThread::msleep(500);
        check_cardState();
        check_cameraState();
    }
}

void MonitorCameraAndCardStateThread::check_cameraState()
{
    check_cameraState1();
    check_cameraState2();
    check_cameraState3();
    check_cameraState4();
}

void MonitorCameraAndCardStateThread::check_cameraState1()
{
    auto& globalStruct = GlobalStructData::getInstance();

    if (globalStruct.camera1) {
        if (globalStruct.camera1->getConnectState()) {
            emit updateCameraLabelState(1, true);
        }
        else {
            emit updateCameraLabelState(1, false);
        }
    }
    else {
        emit updateCameraLabelState(1, false);
    }
}

void MonitorCameraAndCardStateThread::check_cameraState2()
{
    auto& globalStruct = GlobalStructData::getInstance();

    if (globalStruct.camera2) {
        if (globalStruct.camera2->getConnectState()) {
            emit updateCameraLabelState(2, true);
        }
        else {
            emit updateCameraLabelState(2, false);
        }
    }
    else {
        emit updateCameraLabelState(2, false);
    }
}

void MonitorCameraAndCardStateThread::check_cameraState3()
{
    auto& globalStruct = GlobalStructData::getInstance();
    if (globalStruct.camera3) {
        if (globalStruct.camera3->getConnectState()) {
            emit updateCameraLabelState(3, true);
        }
        else {
            emit updateCameraLabelState(3, false);
        }
    }
    else {
        emit updateCameraLabelState(3, false);
    }
}

void MonitorCameraAndCardStateThread::check_cameraState4()
{
    auto& globalStruct = GlobalStructData::getInstance();
    if (globalStruct.camera4) {
        if (globalStruct.camera4->getConnectState()) {
            emit updateCameraLabelState(4, true);
        }
        else {
            emit updateCameraLabelState(4, false);
        }
    }
    else {
        emit updateCameraLabelState(4, false);
    }
}

void MonitorCameraAndCardStateThread::check_cardState()
{
    auto& globalStruct = GlobalStructData::getInstance();

    auto& motionPtr = zwy::scc::GlobalMotion::getInstance().motionPtr;

    bool  boardState = motionPtr.get()->getBoardState();
    if (boardState == false)
    {
        auto openRusult = motionPtr.get()->OpenBoard((char*)"192.168.0.11");
        if (openRusult) {
            emit updateCardLabelState(true);
        }
        else {
            emit updateCardLabelState(false);
        }
    }
    else
    {
        emit updateCardLabelState(false);
    }

}
