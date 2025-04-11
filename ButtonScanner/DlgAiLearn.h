#pragma once
#include <opencv2/opencv.hpp>
#include <QDialog>
#include "ui_DlgAiLearn.h"
#include "cdm_ButtonScannerDlgAiLearn.h"
#include"ImageProcessorModule.h"
#include"ime_ModelEngine.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgAiLearnClass; };
QT_END_NAMESPACE

class DlgAiLearn : public QDialog
{
	Q_OBJECT

public:
	DlgAiLearn(QWidget* parent = nullptr);
	~DlgAiLearn();
private:
	void Init();
	void ToStep1();
	void ToStep2();
	void connects();
	void clearStep();
private:
	Ui::DlgAiLearnClass* ui{ nullptr };
	rw::ime::ModelEngine* _modelEnginePtr{ nullptr };
	rw::cdm::ButtonScannerDlgAiLearn* aiLearnConfig{ nullptr };
	QProcess  m_Process;
	double progress;
	int step{ 0 };
	int moveLen{ 3000 };

	int widget_create_rawX{ 160 };
	int widget_create_rawY{ 120 };
	int widget_check_rawX{ 580 };
	int widget_check_rawY{ 50 };
	int widget_step_rawX{ 970 };
	int widget_step_rawY{ 100 };
	int widget_pic_rawX{ 20 };
	int widget_pic_rawY{ 30 };


private slots:
	void pbtn_yes_clicked();
	void pbtn_no_clicked();
	void pbtn_checkColor_clicked();
	void pbtn_checkKnifeShape_clicked();
	void pbtn_close_clicked();
	void pbtn_pre_clicked();
	void pbtn_next_clicked();
	void pbtn_lookAllImage_clicked();

	void rbtn_station1_checked(bool checked);
	void rbtn_station2_checked(bool checked);
	void rbtn_station3_checked(bool checked);
	void rbtn_station4_checked(bool checked);

	void onFrameCapturedBad(cv::Mat frame, size_t index);
	void pbtn_train_clicked();
	void pbtn_test_clicked();

	void ProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
	void ProcessReadStandardOutput(); 
	void ProcessReadStandardError();
};
