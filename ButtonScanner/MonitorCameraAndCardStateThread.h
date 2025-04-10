#pragma once
#include <QThread>
#include <QDebug>
#include <atomic>

class MonitorCameraAndCardStateThread : public QThread
{
    Q_OBJECT
public:
    explicit MonitorCameraAndCardStateThread(QObject* parent = nullptr);


    ~MonitorCameraAndCardStateThread() override;

    void startThread();

    void stopThread();

protected:
    void run() override;

signals:
    void updateStatisticalInfo();

private:
    std::atomic<bool> running; // 使用原子变量保证线程安全
};