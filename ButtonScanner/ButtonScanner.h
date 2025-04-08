#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ButtonScanner.h"

#include"DlgProduceLineSet.h"
#include"DlgProductSet.h"

#include"opencv2/opencv.hpp"
#include"DlgAiLearn.h"
#include<QImage>
#include<memory>
#include"Product.h"
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
	DlgAiLearn* dlgAiLearn = nullptr;

private:
	//变量监控线程关机的时候停止
	bool mark_Thread = false;
	//踢飞产品数组
	QVector<Product>Products;

public:
	ButtonScanner(QWidget* parent = nullptr);

	~ButtonScanner();

private:
	void set_radioButton();

private:
	void build_ui();
	void build_MainWindowData();
	void build_dlgProduceLineSet();
	void build_dlgProductSet();
	void build_dlgAiLearn();

	void build_connect();
private:
	//read_cofig必须在最前面运行
	void read_config();
	void read_config_mainWindowConfig();
	void read_config_produceLineConfig();
	void read_config_productSetConfig();

	void build_camera();

	void build_ImageProcessorModule();

	void start_monitor();

	void build_Motion();

	//实时监控运动控制卡,相机状态（掉线重连）
	void build_MonitoringThread();

	//开启线程实施监控皮带运动位置
	void build_LOcationThread();
	//开启线程监控运动控制卡io点并且做出相应的逻辑
	void build_IOThread();

private:
	Ui::ButtonScannerClass* ui;

private:
	QImage cvMatToQImage(const cv::Mat& mat);

private slots:
	void _camera1Display(QImage image);

	void _camera2Display(QImage image);

	void _camera3Display(QImage image);

	void _camera4Display(QImage image);

private slots:
	void pbtn_exit_clicked();
	void pbtn_set_clicked();
	void pbtn_newProduction_clicked();
	void pbtn_lightValue_clicked();
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
