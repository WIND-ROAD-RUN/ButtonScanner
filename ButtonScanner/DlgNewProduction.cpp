#include "stdafx.h"
#include "DlgNewProduction.h"

DlgNewProduction::DlgNewProduction(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgNewProductionClass())
{
	ui->setupUi(this);
	build_ui();
	build_connect();
}

DlgNewProduction::~DlgNewProduction()
{
	delete ui;
}

void DlgNewProduction::build_ui()
{
	ui->tabWidget->tabBar()->hide();
	build_dialog();
}

void DlgNewProduction::build_connect()
{
	//tab1
	QObject::connect(ui->pbtn_tab1_exit, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab1_exit_clicked);
	QObject::connect(ui->pbtn_tab1_no, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab1_no_clicked);
	QObject::connect(ui->pbtn_tab1_ok, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab1_ok_clicked);
	//tab2
	QObject::connect(ui->pbtn_tab2_checkColor, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab2_checkColor_clicked);
	QObject::connect(ui->pbtn_tab2_checkBladeShape, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab2_checkBladeShape_clicked);
	QObject::connect(ui->pbtn_tab2_preStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab2_preStep_clicked);
	QObject::connect(ui->pbtn_tab2_exit, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab2_exit_clicked);
	//tab3
	QObject::connect(ui->pbtn_tab3_openImgLocate, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab3_openImgLocate_clicked);
	QObject::connect(ui->pbtn_tab3_exit, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab3_exit_clicked);
	QObject::connect(ui->pbtn_tab3_preStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab3_preStep_clicked);
	QObject::connect(ui->pbtn_tab3_nexStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab3_nexStep_clicked);
	//tab4
	QObject::connect(ui->pbtn_tab4_openImgLocate, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab4_openImgLocate_clicked);
	QObject::connect(ui->pbtn_tab4_exit, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab4_exit_clicked);
	QObject::connect(ui->pbtn_tab4_preStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab4_preStep_clicked);
	QObject::connect(ui->pbtn_tab4_nexStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab4_nexStep_clicked);
	//tab5
	QObject::connect(ui->pbtn_tab5_startTrain, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab5_startTrain_clicked);
	QObject::connect(ui->pbtn_tab5_exit, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab5_exit_clicked);
	QObject::connect(ui->pbtn_tab5_preStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab5_preStep_clicked);
	QObject::connect(ui->pbtn_tab5_finish, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab5_finish_clicked);
}

void DlgNewProduction::build_dialog()
{
	ui->tabWidget->setCurrentIndex(0);
}

void DlgNewProduction::destroy()
{
	_info.state = DlgNewProductionInfo::None;
	ui->tabWidget->setCurrentIndex(0);
	this->hide();
}

void DlgNewProduction::pbtn_tab1_no_clicked()
{
	ui->tabWidget->setCurrentIndex(1);
}

void DlgNewProduction::pbtn_tab1_exit_clicked()
{
	destroy();
}

void DlgNewProduction::pbtn_tab2_checkColor_clicked()
{
	ui->rbtn_tab3_filterColor->setChecked(true);
	ui->rbtn_tab4_filterColor->setChecked(true);
	ui->rbtn_tab5_filterColor->setChecked(true);
	this->_info.state = _info.state = DlgNewProductionInfo::CheckColor;
	ui->tabWidget->setCurrentIndex(2);
}

void DlgNewProduction::pbtn_tab2_checkBladeShape_clicked()
{
	ui->rbtn_tab3_filterColor->setChecked(false);
	ui->rbtn_tab4_filterColor->setChecked(false);
	ui->rbtn_tab5_filterColor->setChecked(false);
	this->_info.state = _info.state = DlgNewProductionInfo::CheckBladeShape;
	ui->tabWidget->setCurrentIndex(2);
}

void DlgNewProduction::pbtn_tab2_preStep_clicked()
{
	ui->tabWidget->setCurrentIndex(0);
}

void DlgNewProduction::pbtn_tab2_exit_clicked()
{
	destroy();

}

void DlgNewProduction::pbtn_tab3_openImgLocate_clicked()
{
}

void DlgNewProduction::pbtn_tab3_exit_clicked()
{
	destroy();
}

void DlgNewProduction::pbtn_tab3_preStep_clicked()
{
	ui->tabWidget->setCurrentIndex(1);
	this->_info.state = _info.state = DlgNewProductionInfo::None;
	ui->rbtn_tab3_filterColor->setChecked(false);
	ui->rbtn_tab4_filterColor->setChecked(false);
	ui->rbtn_tab5_filterColor->setChecked(false);
}

void DlgNewProduction::pbtn_tab3_nexStep_clicked()
{
	ui->tabWidget->setCurrentIndex(3);
}

void DlgNewProduction::pbtn_tab4_openImgLocate_clicked()
{
}

void DlgNewProduction::pbtn_tab4_exit_clicked()
{
	destroy();
}

void DlgNewProduction::pbtn_tab4_preStep_clicked()
{
	ui->tabWidget->setCurrentIndex(2);
}

void DlgNewProduction::pbtn_tab4_nexStep_clicked()
{
	ui->tabWidget->setCurrentIndex(4);
}

void DlgNewProduction::pbtn_tab5_startTrain_clicked()
{
}

void DlgNewProduction::pbtn_tab5_exit_clicked()
{
	destroy();
}	

void DlgNewProduction::pbtn_tab5_preStep_clicked()
{
	ui->tabWidget->setCurrentIndex(3);
}

void DlgNewProduction::pbtn_tab5_finish_clicked()
{
	destroy();
}

void DlgNewProduction::pbtn_tab1_ok_clicked()
{
	ui->tabWidget->setCurrentIndex(1);
}
