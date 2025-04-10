#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ButtonScanner.h"

#include"DlgProduceLineSet.h"
#include"DlgProductSet.h"
#include"DlgExposureTimeSet.h"

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
    DlgProduceLineSet* dlgProduceLineSet = nullptr;
    DlgProductSet* dlgProductSet = nullptr;
    DlgExposureTimeSet* dlgExposureTimeSet = nullptr;

private:
    //变量监控线程关机的时候停止
    bool mark_Thread = false;
public:
    QRect exposureTimeTriggerArea; // 指定区域
    float exposureTimeTriggerWidthRatio = 0.3f;  
    float exposureTimeTriggerRatio = 0.3f; 
private:
    void updateExposureTimeTrigger();
    void onExposureTimeTriggerAreaClicked();
protected:
    void mousePressEvent(QMouseEvent* event)override;
    void resizeEvent(QResizeEvent* event) override;
public:
    ButtonScanner(QWidget* parent = nullptr);

    ~ButtonScanner();

private:
    void set_radioButton();

private:
    void build_ui();
    void build_mainWindowData();
    void build_dlgProduceLineSet();
    void build_dlgProductSet();
    void build_dlgExposureTimeSet();

    void build_connect();
private:
    //read_cofig必须在最前面运行
    void read_config();
    void read_config_mainWindowConfig();
    void read_config_produceLineConfig();
    void read_config_productSetConfig();
    void read_config_exposureTimeSetConfig();

public:
    void build_imageSaveEngine();

    void clear_olderSavedImage();

    void build_camera();

    void build_imageProcessorModule();

    void start_monitor();

    void build_motion();

    //实时监控运动控制卡,相机状态（掉线重连）
    void build_monitoringThread();

    //开启线程实施监控皮带运动位置
    void build_locationThread();
    //开启线程监控运动控制卡io点并且做出相应的逻辑
    void build_ioThread();

private:
    Ui::ButtonScannerClass* ui;

private:
    QImage cvMatToQImage(const cv::Mat& mat);

private slots:
    void onCamera1Display(QImage image);

    void onCamera2Display(QImage image);

    void onCamera3Display(QImage image);

    void onCamera4Display(QImage image);

private slots:
    void pbtn_exit_clicked();
    void pbtn_set_clicked();
    void pbtn_newProduction_clicked();
    void pbtn_beltSpeed_clicked();
    void pbtn_score_clicked();

    void rbtn_debug_ckecked(bool checked);
    void rbtn_takePicture_ckecked(bool checked);
    void rbtn_removeFunc_ckecked(bool checked);
    void rbtn_upLight_ckecked(bool checked);
    void rbtn_sideLight_ckecked(bool checked);
    void rbtn_downLight_ckecked(bool checked);
    void rbtn_defect_ckecked(bool checked);
    void rbtn_ForAndAgainst_ckecked(bool checked);
};
