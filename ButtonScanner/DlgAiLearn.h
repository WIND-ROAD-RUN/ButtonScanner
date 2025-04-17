#pragma once
#include <opencv2/opencv.hpp>
#include <QDialog>
#include "ui_DlgAiLearn.h"
#include "cdm_ButtonScannerDlgAiLearn.h"
#include"ImageProcessorModule.h"
#include"imest_ModelEngineST.h"

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
	rw::cdm::ButtonScannerDlgAiLearn* read_lastConfig();
	rw::cdm::ButtonScannerDlgAiLearn* read_config(const QString& path);
	rw::cdm::ButtonScannerDlgAiLearn* get_newConfig();
	void save_config(const rw::cdm::ButtonScannerDlgAiLearn* config);

private:
	void build_connect();
public:
	void build_ui();
	void ToStep1();
	void ToStep2();
	void clearStep();
public:
	int step{ 0 };
private:
	Ui::DlgAiLearnClass* ui{ nullptr };
	rw::imest::ModelEngineST* _modelEnginePtr{ nullptr };
	rw::cdm::ButtonScannerDlgAiLearn* aiLearnConfig;
	QProcess  m_Process;

	int moveLen{ 3000 };

	int widget_create_rawX{ 160 };
	int widget_create_rawY{ 120 };
	int widget_check_rawX{ 580 };
	int widget_check_rawY{ 50 };
	int widget_step_rawX{ 720 };
	int widget_step_rawY{ 10 };
	int widget_pic_rawX{ 20 };
	int widget_pic_rawY{ 30 };
	int widget_progress_rawX{ 50 };
	int widget_progress_rawY{ 50 };
	int txt_log_rawX{ 50 };
	int txt_log_rawY{ 230 };
	int pbtn_tranCompelete_rawX{ 350 };
	int pbtn_tranCompelete_rawY{ 135 };

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


	void pbtn_train_clicked();
	void pbtn_test_clicked();
	void pbtn_tranCompelete_clicked();

	void ProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

	void ProcessReadOut();

public slots:
	void onFrameCaptured(cv::Mat frame, size_t index);

};
