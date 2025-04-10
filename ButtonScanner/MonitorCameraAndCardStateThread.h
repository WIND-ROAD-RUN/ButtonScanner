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
private:
    void check_cameraState();
    void check_cameraState1();
    void check_cameraState2();
    void check_cameraState3();
    void check_cameraState4();
private:
    void check_cardState();

signals:
    void updateCameraLabelState(int cameraIndex, bool state);
    void updateCardLabelState(bool state);

private:
    std::atomic<bool> running; // 使用原子变量保证线程安全
};