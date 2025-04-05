#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ButtonScanner.h"
#include<memory>
#include"opencv2/opencv.hpp"
#include<QImage>

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
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera1;
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera2;
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera3;
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera4;

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
    void start_monitor();
    //初始化运动控制卡
    void build_Motion();

    //实时监控运动控制卡状态（掉线重连）



    //实时监控相机链接状态（掉线重连）



    //开启线程实施监控皮带运动位置



    //开启线程监控运动控制卡io点并且做出相应的逻辑





private:
    Ui::ButtonScannerClass *ui;

private:
    QImage cvMatToQImage(const cv::Mat& mat);

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
