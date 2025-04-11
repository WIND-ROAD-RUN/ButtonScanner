#include "stdafx.h"
#include "DlgAiLearn.h"
#include <GlobalStruct.h>
#include <PathGlobalStruct.h>
#include <windows.h>
#include <codecvt>
#include <AiLearnTools.h>
#include"ime_ModelEngine.h"

DlgAiLearn::DlgAiLearn(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgAiLearnClass())
{
	ui->setupUi(this);

	ui->label_pic1->setScaledContents(true);
	ui->label_pic2->setScaledContents(true);
	ui->label_pic3->setScaledContents(true);
	ui->label_pic4->setScaledContents(true);

	Init();
	connects();
}

DlgAiLearn::~DlgAiLearn()
{
	delete aiLearnConfig;

	delete _modelEnginePtr;

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
	QObject::connect(ui->pbtn_train, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_train_clicked);
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

	QObject::connect(ui->pbtn_test, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_test_clicked);
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
	auto& globalStruct = GlobalStruct::getInstance();

	_modelEnginePtr = new rw::ime::ModelEngine(globalStruct.enginePath.toStdString(), globalStruct.namePath.toStdString());

	auto tempConfig = rw::cdm::ButtonScannerDlgAiLearn::ReadLastConfig();
	if (tempConfig == nullptr)
		ui->pbtn_no->setVisible(false);
	delete tempConfig;

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

	AiLearnTools::MakeDir(path);

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

void DlgAiLearn::onFrameCapturedBad(cv::Mat frame, size_t index)
{
	std::vector<rw::ime::ProcessRectanglesResult> vecRecogResult;
	cv::Mat resultImage;
	cv::Mat maskImage = cv::Mat::zeros(frame.size(), CV_8UC1);
	_modelEnginePtr->ProcessMask(frame, resultImage, maskImage, vecRecogResult);

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

		auto dateTimeStr = QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz").toStdString();
		bool isBad = step == 1;

		AiLearnTools::SaveImage(frame, aiLearnConfig->learnInfoSign, dateTimeStr, isBad, index);
		AiLearnTools::SaveYoloText(aiLearnConfig->learnInfoSign, dateTimeStr, isBad, aiLearnConfig->checkType,
			centerX, centerY, width, height, frame.cols, frame.rows);

		auto qImage = AiLearnTools::cvMat2QImage(frame);
		QPixmap qPixmap = QPixmap::fromImage(qImage);
		if (index == 1)
			QMetaObject::invokeMethod(ui->label_pic1, "setPixmap", Qt::QueuedConnection, Q_ARG(QPixmap, qPixmap));
		if (index == 2)
			QMetaObject::invokeMethod(ui->label_pic2, "setPixmap", Qt::QueuedConnection, Q_ARG(QPixmap, qPixmap));
		if (index == 3)
			QMetaObject::invokeMethod(ui->label_pic3, "setPixmap", Qt::QueuedConnection, Q_ARG(QPixmap, qPixmap));
		if (index == 4)
			QMetaObject::invokeMethod(ui->label_pic4, "setPixmap", Qt::QueuedConnection, Q_ARG(QPixmap, qPixmap));
	}

	auto dateTimeStr = QDateTime::currentDateTime().toString("yyyyMMddHHmmsszzz").toStdString();
	AiLearnTools::SaveImage(frame, aiLearnConfig->learnInfoSign, dateTimeStr, true, index);
	AiLearnTools::SaveYoloText(aiLearnConfig->learnInfoSign, dateTimeStr, true, aiLearnConfig->checkType,
		500, 500, 200, 210, frame.cols, frame.rows);

	auto qImage = AiLearnTools::cvMat2QImage(frame);
	QPixmap qPixmap = QPixmap::fromImage(qImage);
	if (index == 1)
		QMetaObject::invokeMethod(ui->label_pic1, "setPixmap", Qt::QueuedConnection, Q_ARG(QPixmap, qPixmap));
	if (index == 2)
		QMetaObject::invokeMethod(ui->label_pic2, "setPixmap", Qt::QueuedConnection, Q_ARG(QPixmap, qPixmap));
	if (index == 3)
		QMetaObject::invokeMethod(ui->label_pic3, "setPixmap", Qt::QueuedConnection, Q_ARG(QPixmap, qPixmap));
	if (index == 4)
		QMetaObject::invokeMethod(ui->label_pic4, "setPixmap", Qt::QueuedConnection, Q_ARG(QPixmap, qPixmap));
}

void DlgAiLearn::pbtn_train_clicked()
{
	//训练之前删除之前的train
	QDir dir("D:\\y\\yolov5-master\\runs\\train");
	dir.rmdir(dir.absolutePath());

	disconnect(&m_Process, &QProcess::readyReadStandardError, this, &DlgAiLearn::ProcessReadStandardError);//读就绪
	disconnect(&m_Process, &QProcess::readyReadStandardOutput, this, &DlgAiLearn::ProcessReadStandardOutput);//标准读就绪
	disconnect(&m_Process, &QProcess::finished, this, &DlgAiLearn::ProcessFinished);//进程完成
	connect(&m_Process, &QProcess::readyReadStandardError, this, &DlgAiLearn::ProcessReadStandardError);//读就绪
	connect(&m_Process, &QProcess::readyReadStandardOutput, this, &DlgAiLearn::ProcessReadStandardOutput);//标准读就绪
	connect(&m_Process, &QProcess::finished, this, &DlgAiLearn::ProcessFinished);//进程完成

	m_Process.start("cmd.exe", { "/c", "activate yolov5 && cd /d D:\\y\\yolov5-master\\ && python train.py" });

	//QString mess = "activate yolov5";
	//mess.append("\r\n");
	//char* ch;
	//QByteArray ba = mess.toLatin1(); //
	//ch = ba.data();
	//m_Process.write(ch);
	
	//mess = "cd /d D:\\y\\yolov5-master\\";
	//mess.append("\r\n");
	//ba = mess.toLatin1(); //
	//ch = ba.data();
	//m_Process.write(ch);

	//auto dataYamlPath = AiLearnTools::SaveYoloDataYaml(aiLearnConfig->learnInfoSign);
	////mess = QString("python train.py --data \"%1\"").arg(QString::fromStdString(dataYamlPath));
	//mess = QString("python train.py");
	//mess.append("\r\n");
	//ba = mess.toLatin1(); //
	//ch = ba.data();
	//m_Process.write(ch);

}

void DlgAiLearn::pbtn_test_clicked()
{
	std::string image_path = R"(C:\Users\admin\Desktop\111705305392.jpg)";  // Windows 示例

	// 读取图片到 cv::Mat
	cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);  // 默认以彩色模式读取

	if (ui->rbtn_station1->isChecked())
		onFrameCapturedBad(image, 1);
	if (ui->rbtn_station2->isChecked())
		onFrameCapturedBad(image, 2);
	if (ui->rbtn_station3->isChecked())
		onFrameCapturedBad(image, 3);
	if (ui->rbtn_station4->isChecked())
		onFrameCapturedBad(image, 4);

}

void DlgAiLearn::ProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	if (exitStatus == QProcess::NormalExit)
	{
		qDebug() << "进来";
		//QProcess* processRobot_1 = new QProcess();
		//processRobot_1->start("cmd.exe");
		//processRobot_1->write("activate yolov5");
		//processRobot_1->write("&&");
		////qDebug()<<mess;
		// //processRobot_1->write((char*)(mess.toStdString().c_str()));
		//processRobot_1->write("cd /d D:\\y\\yolov5-6.0\\ && start python export.py\n ");

	}
	else
	{
		//程序异常结束
		qDebug() << "进来2";

	}
}

void DlgAiLearn::ProcessReadStandardOutput()
{
	qDebug() << "Output" << m_Process.readAllStandardOutput().toStdString();
	//QString lastend = "Optimizer stripped from runs\\train\\exp\\weights\\last.pt";
	//int bpos = msg.indexOf(lastend);
	//if (bpos != -1)
	//{

	//	emit isfinishTrain();

	//}
	//lastend = "--weights runs\\train\\exp\\weights\\best.onnx";
	//bpos = msg.indexOf(lastend);
	//if (bpos != -1)
	//{

	//	emit isfinishExport();

	//}

	//dvalue = dvalue + 0.5;



	//value = dvalue;
	//if (value < 90)
	//{

	//	ui->progressBar->setValue(value);  // 当前进度

	//}
}

void DlgAiLearn::ProcessReadStandardError()
{
	qDebug()<<"Error" << m_Process.readAllStandardError().toStdString();
}

