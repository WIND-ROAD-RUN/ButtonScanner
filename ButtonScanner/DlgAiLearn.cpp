#include "stdafx.h"
#include "DlgAiLearn.h"
#include <GlobalStruct.h>
#include <PathGlobalStruct.h>
#include <windows.h>
#include <codecvt>

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

	QObject::connect(ui->pbtn_lookAllImage, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_lookAllImage_clicked);
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
	if (rw::cdm::ButtonScannerDlgAiLearn::ReadLastConfig() == nullptr)
		ui->pbtn_no->setVisible(false);

	ui->rbtn_filterColorDiff->setEnabled(false);

	ui->widget_create->move(widget_create_rawX, widget_create_rawY);
	ui->widget_check->move(moveLen, 0);
	ui->widget_step->move(moveLen, 0);
	ui->widget_pic->move(moveLen, 0);
}

void DlgAiLearn::ToStep1()
{
	clearStep();
	step = 1;
	ui->label_stepTitle->setText("第一步:");
	ui->label_stepDescribe->setText("放要筛选的纽扣");

	ui->widget_create->move(moveLen, 0);

	ui->pbtn_pre->setVisible(false);

	if (aiLearnConfig->checkType == 1)
		ui->rbtn_filterColorDiff->setChecked(true);
	else
		ui->rbtn_filterColorDiff->setChecked(false);

	ui->widget_pic->move(widget_pic_rawX, widget_pic_rawY);
	ui->widget_step->move(widget_step_rawX, widget_step_rawY);
}

void DlgAiLearn::ToStep2()
{
	clearStep();
	step = 2;
	ui->label_stepTitle->setText("第二步:");
	ui->label_stepDescribe->setText("放好的纽扣");

	ui->widget_create->move(moveLen, 0);

	ui->pbtn_pre->setVisible(true);

	if (aiLearnConfig->checkType == 1)
		ui->rbtn_filterColorDiff->setChecked(true);
	else
		ui->rbtn_filterColorDiff->setChecked(false);

	ui->widget_pic->move(widget_pic_rawX, widget_pic_rawY);
	ui->widget_step->move(widget_step_rawX, widget_step_rawY);
}

void DlgAiLearn::pbtn_yes_clicked() {
	ui->widget_check->move(widget_check_rawX, widget_check_rawY);
}

void DlgAiLearn::pbtn_no_clicked()
{
	aiLearnConfig = rw::cdm::ButtonScannerDlgAiLearn::ReadLastConfig();
	ToStep1();
}

void DlgAiLearn::pbtn_checkColor_clicked()
{
	aiLearnConfig = rw::cdm::ButtonScannerDlgAiLearn::GetNew(1);
	aiLearnConfig->checkType = 1;
	aiLearnConfig->Save();
	ToStep1();
}

void DlgAiLearn::pbtn_checkKnifeShape_clicked()
{
	aiLearnConfig = rw::cdm::ButtonScannerDlgAiLearn::GetNew(2);
	aiLearnConfig->checkType = 2;
	aiLearnConfig->Save();
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

void DlgAiLearn::pbtn_lookAllImage_clicked()
{
	auto path = QString::fromStdString(PathGlobalStruct::AiLearnData + "\\" + aiLearnConfig->learnInfoSign);

	QDir dir = QDir(path);
	qDebug() << "目录路径:" << dir.path();
	if (!dir.exists()) {
		dir.mkpath(".");
	}

	auto wPath = path.toStdWString();
	auto wCharPath = wPath.c_str();
	HINSTANCE result = ShellExecute(NULL, L"open", L"explorer.exe", wCharPath, NULL, SW_SHOW);
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

void DlgAiLearn::onFrameCapturedBad(cv::Mat frame, std::vector<rw::ime::ProcessRectanglesResult> vecRecogResult, size_t index)
{
	std::vector<int> waiJingIndexs = std::vector<int>();
	for (int i = 0; i < vecRecogResult.size(); i++)
	{
		switch (vecRecogResult[i].classId)
		{
		case 0: waiJingIndexs.push_back(i); continue;
		default: continue;
		}
	}

	if (waiJingIndexs.size() == 1) {
		auto width = abs(vecRecogResult[waiJingIndexs[0]].right_bottom.first - vecRecogResult[waiJingIndexs[0]].left_top.first) / 2;
		auto height = abs(vecRecogResult[waiJingIndexs[0]].right_bottom.second - vecRecogResult[waiJingIndexs[0]].left_top.second) / 2;
		auto centerX = vecRecogResult[waiJingIndexs[0]].left_top.first + width;
		auto centerY = vecRecogResult[waiJingIndexs[0]].left_top.second + height;

		vecRecogResult[waiJingIndexs[0]].
		auto dateTimeStr = QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz").toStdString();


	}
}



