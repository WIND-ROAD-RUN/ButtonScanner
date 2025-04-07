#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ButtonScanner.h"

#include"opencv2/opencv.hpp"

#include<QImage>

#include<memory>
namespace rw
{
    namespace rqw
    {
        class CameraPassiveThread;
    }
}

QT_BEGIN_NAMESPACE
namespace Ui { class ButtonScannerClass; };
QT_END_NAMESPACE

class ButtonScanner : public QMainWindow
{
    Q_OBJECT

private:
    //变量监控线程关机的时候停止
    bool mark_Thread = false;

public:
    ButtonScanner(QWidget *parent = nullptr);

    ~ButtonScanner();

private:
    void set_radioButton();

private:
    void build_ui();

    void build_connect();
private:
    void build_camera();

    void build_engine();

    void start_monitor();

    void build_Motion();

    //实时监控运动控制卡,相机状态（掉线重连）
    void build_MonitoringThread();

    //开启线程实施监控皮带运动位置

    //开启线程监控运动控制卡io点并且做出相应的逻辑
    void build_IOThread();

private:
    Ui::ButtonScannerClass *ui;

private:
    QImage cvMatToQImage(const cv::Mat& mat);

    cv::Mat longRunningTask(const cv::Mat& frame, int workindex);

private slots:
    void _camera1Display(cv::Mat frame);

    void _camera2Display(cv::Mat frame);

    void _camera3Display(cv::Mat frame);

    void _camera4Display(cv::Mat frame);

private slots:
    void pbtn_exit_clicked();

    void pbtn_set_clicked();

    void pbtn_newProduction_clicked();

};
