#pragma once

#include <QDialog>
#include "ui_DlgNewProduction.h"

#include"opencv2/opencv.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgNewProductionClass; };
QT_END_NAMESPACE


struct DlgNewProductionInfo
{
	enum State
	{
		None,
		CheckBladeShape,
		CheckColor
	}state;

	std::atomic_bool isActivate{ false };
	size_t currentTabIndex{0};
};

class DlgNewProduction : public QDialog
{
	Q_OBJECT
public:
	DlgNewProduction(QWidget *parent = nullptr);

	~DlgNewProduction();

private:
	void build_ui();
	void build_connect();

private:
	Ui::DlgNewProductionClass *ui;

private:
	void build_dialog();
	void destroy();

private:
	DlgNewProductionInfo _info;
private:
	void img_display_work1(const cv::Mat & frame);
	void img_display_work2(const cv::Mat& frame);
	void img_display_work3(const cv::Mat& frame);
	void img_display_work4(const cv::Mat& frame);
private slots:
	void imgDisplay_work(cv::Mat frame, size_t index);

private slots:
	void pbtn_tab1_ok_clicked();
	void pbtn_tab1_no_clicked();
	void pbtn_tab1_exit_clicked();
private slots:
	void pbtn_tab2_check_color_clicked();
	void pbtn_tab2_check_blade_shape_clicked();
	void pbtn_tab2_pre_step_clicked();
	void pbtn_tab2_exit_clicked();
private slots:
	void pbtn_tab3_open_img_locate_clicked();
	void pbtn_tab3_exit_clicked();
	void pbtn_tab3_pre_step_clicked();
	void pbtn_tab3_nex_step_clicked();
private slots:
	void pbtn_tab4_openImgLocate_clicked();
	void pbtn_tab4_exit_clicked();
	void pbtn_tab4_preStep_clicked();
	void pbtn_tab4_nexStep_clicked();
private slots:
	void pbtn_tab5_startTrain_clicked();
	void pbtn_tab5_exit_clicked();
	void pbtn_tab5_preStep_clicked();
	void pbtn_tab5_finish_clicked();
};
