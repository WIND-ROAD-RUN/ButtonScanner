#pragma once

#include <QDialog>
#include "ui_DlgNewProduction.h"

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
private slots:
	void pbtn_tab1_ok_clicked();
	void pbtn_tab1_no_clicked();
	void pbtn_tab1_exit_clicked();
private slots:
	void pbtn_tab2_checkColor_clicked();
	void pbtn_tab2_checkBladeShape_clicked();
	void pbtn_tab2_preStep_clicked();
	void pbtn_tab2_exit_clicked();
private slots:
	void pbtn_tab3_openImgLocate_clicked();
	void pbtn_tab3_exit_clicked();
	void pbtn_tab3_preStep_clicked();
	void pbtn_tab3_nexStep_clicked();
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
