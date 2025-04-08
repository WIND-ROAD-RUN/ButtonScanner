#include "stdafx.h"
#include "DlgAiLearn.h"

DlgAiLearn::DlgAiLearn(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgAiLearnClass())
{
	ui->setupUi(this);
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
 
}

void DlgAiLearn::Init()
{
	ui->widget_check->move(moveLen, 0);
	ui->widget_step1->move(moveLen, 0);

}

void DlgAiLearn::ToStep1()
{
	ui->widget_create->move(moveLen, 0);
	ui->widget_step1->move(widget_step1_rawX, widget_step1_rawY);
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
	ToStep1();
}

void DlgAiLearn::pbtn_checkKnifeShape_clicked()
{
	ToStep1();
}

void DlgAiLearn::pbtn_close_clicked()
{
	this->close();
}

 

