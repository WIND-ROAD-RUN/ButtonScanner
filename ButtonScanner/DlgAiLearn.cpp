#include "stdafx.h"
#include "DlgAiLearn.h"
#include <GlobalStruct.h>

DlgAiLearn::DlgAiLearn(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgAiLearnClass())
{
	ui->setupUi(this);
	//aiLearnConfig= rw::cdm::ButtonScannerDlgAiLearn::
	Init();
	connects();
}

DlgAiLearn::~DlgAiLearn()
{
	delete ui;
}

void DlgAiLearn::connects()
{
	QObject::connect(ui->pbtn_yes, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_yes_clicked);
	QObject::connect(ui->pbtn_no, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_no_clicked);
	QObject::connect(ui->pbtn_close, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_close_clicked);

	QObject::connect(ui->pbtn_checkColor, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_checkColor_clicked);
	QObject::connect(ui->pbtn_checkKnifeShape, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_checkKnifeShape_clicked);

	QObject::connect(ui->pbtn_pre, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_pre_clicked);
	QObject::connect(ui->pbtn_next, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_next_clicked);

	QObject::connect(ui->rbtn_station1, &QPushButton::clicked,
		this, &DlgAiLearn::rbtn_station1_checked);
	QObject::connect(ui->rbtn_station2, &QPushButton::clicked,
		this, &DlgAiLearn::rbtn_station2_checked);
	QObject::connect(ui->rbtn_station3, &QPushButton::clicked,
		this, &DlgAiLearn::rbtn_station3_checked);
	QObject::connect(ui->rbtn_station4, &QPushButton::clicked,
		this, &DlgAiLearn::rbtn_station4_checked);
	
}

void DlgAiLearn::clearStep()
{
	ui->rbtn_station1->setChecked(false);
	ui->rbtn_station2->setChecked(false);
	ui->rbtn_station3->setChecked(false);
	ui->rbtn_station4->setChecked(false);
	ui->label_pic1->clear();
	ui->label_pic2->clear();
	ui->label_pic3->clear();
	ui->label_pic4->clear();
}

void DlgAiLearn::Init()
{
	ui->rbtn_filterColorDiff->setEnabled(false);

	ui->widget_create->move(widget_create_rawX, widget_create_rawY);
	ui->widget_check->move(moveLen, 0);
	ui->widget_step->move(moveLen, 0);
	ui->widget_pic->move(moveLen, 0);

	/*if (aiLearnConfig->checkType == 0)
		ui->pbtn_no->setVisible(false);*/
}

void DlgAiLearn::ToStep1()
{
	clearStep();

	ui->label_stepTitle->setText("第一步:");
	ui->label_stepDescribe->setText("放要筛选的纽扣");

	ui->widget_create->move(moveLen, 0);

	ui->pbtn_pre->setVisible(false);
	/*if (aiLearnConfig->checkType == 1)
		ui->rbtn_filterColorDiff->setChecked(true);
	else
		ui->rbtn_filterColorDiff->setChecked(false);*/

	ui->widget_pic->move(widget_pic_rawX, widget_pic_rawY);
	ui->widget_step->move(widget_step_rawX, widget_step_rawY);
}

void DlgAiLearn::ToStep2()
{
	clearStep();

	ui->label_stepTitle->setText("第二步:");
	ui->label_stepDescribe->setText("放好的纽扣");

	ui->widget_create->move(moveLen, 0);

	ui->pbtn_pre->setVisible(true);
	/*if (aiLearnConfig->checkType == 1)
		ui->rbtn_filterColorDiff->setChecked(true);
	else
		ui->rbtn_filterColorDiff->setChecked(false);*/

	ui->widget_pic->move(widget_pic_rawX, widget_pic_rawY);
	ui->widget_step->move(widget_step_rawX, widget_step_rawY);
}

void DlgAiLearn::pbtn_yes_clicked() {
	ui->widget_check->move(widget_check_rawX, widget_check_rawY);
}

void DlgAiLearn::pbtn_no_clicked()
{
	ToStep1();
}

void DlgAiLearn::pbtn_checkColor_clicked()
{
	//aiLearnConfig->checkType = 1;
	//GlobalStruct::getInstance().saveDlgAiLearnConfig();
	ToStep1();
}

void DlgAiLearn::pbtn_checkKnifeShape_clicked()
{
	//aiLearnConfig->checkType = 2;
	//GlobalStruct::getInstance().saveDlgAiLearnConfig();
	ToStep1();
}

void DlgAiLearn::pbtn_close_clicked()
{
	this->close();
}

void DlgAiLearn::pbtn_pre_clicked()
{
	ToStep1();
}

void DlgAiLearn::pbtn_next_clicked()
{
	ToStep2();
}

void DlgAiLearn::rbtn_station1_checked(bool checked)
{
}

void DlgAiLearn::rbtn_station2_checked(bool checked)
{
}

void DlgAiLearn::rbtn_station3_checked(bool checked)
{
}

void DlgAiLearn::rbtn_station4_checked(bool checked)
{
}



