#include"stdafx.h"

#include"MonitorCameraAndCardStateThread.h"

MonitorCameraAndCardStateThread::MonitorCameraAndCardStateThread(QObject* parent)
    : QThread(parent), running(false) {
}

MonitorCameraAndCardStateThread::~MonitorCameraAndCardStateThread()
{
    stopThread();
    wait(); // 等待线程安全退出
}

void MonitorCameraAndCardStateThread::startThread()
{
    running = true;
    if (!isRunning()) {
        start(); // 启动线程
    }
}

void MonitorCameraAndCardStateThread::stopThread()
{
    running = false; // 停止线程
}

void MonitorCameraAndCardStateThread::run()
{
    
    while (running) {
       
        // 每3秒计算一次
        QThread::sleep(3);



    }
}
