#include "stdafx.h"
#include"StatisticalInfoComputingThread.h"

#include"GlobalStruct.h"

StatisticalInfoComputingThread::StatisticalInfoComputingThread(QObject* parent)
    : QThread(parent), running(false) {
}

StatisticalInfoComputingThread::~StatisticalInfoComputingThread()
{
    stopThread();
    wait(); // 等待线程安全退出
}

void StatisticalInfoComputingThread::startThread()
{
    running = true;
    if (!isRunning()) {
        start(); // 启动线程
    }
}

void StatisticalInfoComputingThread::stopThread()
{
    running = false; // 停止线程
}

void StatisticalInfoComputingThread::run()
{
    auto& globalStruct = GlobalStructData::getInstance();
    auto& statisticalInfo = globalStruct.statisticalInfo;
    while (running) {
        auto olderWasteCount = statisticalInfo.wasteCount.load();
        // 每3秒计算一次
        QThread::sleep(1); 
        // 计算去除率
        auto newWasteCount = statisticalInfo.wasteCount.load();
        auto rate = static_cast<double>(newWasteCount - olderWasteCount) *12;
        statisticalInfo.removeRate = rate;



        // 计算生产良率
        auto totalCount = statisticalInfo.produceCount.load();
        auto wasteCount = statisticalInfo.wasteCount.load();
        statisticalInfo.productionYield = (static_cast<double>(totalCount - wasteCount) / totalCount) * 100;

        // 发送信号更新UI
        emit updateStatisticalInfo();


    }
}