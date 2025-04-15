#include "stdafx.h"
#include "DlgAiLearn.h"
#include <GlobalStruct.h>
#include <PathGlobalStruct.h>
#include <windows.h>
#include <codecvt>
#include <AiLearnTools.h>
#include"ime_ModelEngine.h"
#include <algorithm> 

DlgAiLearn::DlgAiLearn(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgAiLearnClass())
{
	ui->setupUi(this);

	ui->label_pic1->setScaledContents(true);
	ui->label_pic2->setScaledContents(true);
	ui->label_pic3->setScaledContents(true);
	ui->label_pic4->setScaledContents(true);

	build_ui();
	build_connect();
}

DlgAiLearn::~DlgAiLearn()
{
	delete _modelEnginePtr;
	delete  aiLearnConfig;
	delete ui;
}

rw::cdm::ButtonScannerDlgAiLearn* DlgAiLearn::read_lastConfig()
{
	QString targetDir = QString::fromStdString(PathGlobalStruct::AiLearnConfig);
	QDir dir(targetDir);
	if (!dir.exists()) {
		return nullptr;
	}
	QStringList filters;
	QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);

	if (fileInfoList.isEmpty()) {
		return nullptr;
	}

	QFileInfo maxFile = fileInfoList.last();

	return read_config(maxFile.absoluteFilePath());
}

rw::cdm::ButtonScannerDlgAiLearn* DlgAiLearn::read_config(const QString& path)
{
	auto _StoreContext = std::make_unique<rw::oso::StorageContext>(rw::oso::StorageType::Xml);
	QDir dir;

	QFileInfo dlgAiLearnFile(path);
	if (!dlgAiLearnFile.exists()) {
		/*auto config = rw::cdm::ButtonScannerDlgAiLearn();
		save_config(config);
		return config;*/
		return  nullptr;
	}
	else {
		auto assembly = _StoreContext->load(path.toStdString());
		if (assembly) {
			auto loadDlgAiLearnConfig = new rw::cdm::ButtonScannerDlgAiLearn(*assembly);
			return loadDlgAiLearnConfig;
		}
	}
}

rw::cdm::ButtonScannerDlgAiLearn* DlgAiLearn::get_newConfig()
{
	auto temp = new rw::cdm::ButtonScannerDlgAiLearn();
	temp->learnInfoSign = QDateTime::currentDateTime().toString("yyyyMMddHHmmss").toStdString();
	save_config(temp);
	return temp;
}

void DlgAiLearn::save_config(const rw::cdm::ButtonScannerDlgAiLearn* config)
{
	QString pathQt = QString::fromStdString(PathGlobalStruct::AiLearnConfig + "\\" + config->learnInfoSign);

	QFileInfo dlgAiLearnFile(pathQt);
	if (!dlgAiLearnFile.exists()) {
		QDir configDir = QFileInfo(pathQt).absoluteDir();
		if (!configDir.exists()) {
			configDir.mkpath(".");
		}
		QFile file(pathQt);
		if (file.open(QIODevice::WriteOnly)) {
			file.close();
		}
	}

	auto& globalStrut = GlobalStructData::getInstance();
	globalStrut.storeContext->save(*config, pathQt.toStdString());
}


void DlgAiLearn::build_connect()
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

	QObject::connect(ui->pbtn_tranCompelete, &QPushButton::clicked,
		this, &DlgAiLearn::pbtn_tranCompelete_clicked);
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

void DlgAiLearn::build_ui()
{
	auto& globalStruct = GlobalStructData::getInstance();

	_modelEnginePtr = new rw::ime::ModelEngine(globalStruct.enginePath.toStdString(), globalStruct.namePath.toStdString());

	aiLearnConfig = read_lastConfig();
	if (!GlobalStructData::getInstance().aiLearnOldConfigPath.isEmpty())
		aiLearnConfig = read_config(GlobalStructData::getInstance().aiLearnOldConfigPath);

	if (aiLearnConfig == nullptr)
	{
		ui->pbtn_no->setVisible(false);
	}


	ui->rbtn_filterColorDiff->setEnabled(false);

	ui->widget_progress->move(moveLen, 0);
	ui->widget_create->move(widget_create_rawX, widget_create_rawY);
	ui->widget_check->move(moveLen, 0);
	ui->widget_step->move(moveLen, 0);
	ui->widget_pic->move(moveLen, 0);
	ui->pbtn_tranCompelete->move(moveLen, 0);

	ui->txt_log->move(moveLen, 0);
	ui->txt_log->setReadOnly(true);
	ui->txt_log->setWordWrapMode(QTextOption::WordWrap);

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
	GlobalStructData& globalStruct = GlobalStructData::getInstance();
	globalStruct.mainWindowConfig.upLight = aiLearnConfig->upLight;
	globalStruct.mainWindowConfig.downLight = aiLearnConfig->downLight;
	globalStruct.mainWindowConfig.sideLight = aiLearnConfig->sideLight;

	ToStep1();
}

void DlgAiLearn::pbtn_checkColor_clicked()
{
	GlobalStructData& globalStruct = GlobalStructData::getInstance();

	aiLearnConfig = get_newConfig();
	aiLearnConfig->checkType = 1;
	aiLearnConfig->upLight = globalStruct.mainWindowConfig.upLight;
	aiLearnConfig->downLight = globalStruct.mainWindowConfig.downLight;
	aiLearnConfig->sideLight = globalStruct.mainWindowConfig.sideLight;
	save_config(aiLearnConfig);

	ToStep1();
}

void DlgAiLearn::pbtn_checkKnifeShape_clicked()
{
	GlobalStructData& globalStruct = GlobalStructData::getInstance();

	aiLearnConfig = get_newConfig();
	aiLearnConfig->checkType = 2;
	aiLearnConfig->upLight = globalStruct.mainWindowConfig.upLight;
	aiLearnConfig->downLight = globalStruct.mainWindowConfig.downLight;
	aiLearnConfig->sideLight = globalStruct.mainWindowConfig.sideLight;
	save_config(aiLearnConfig);

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
	setAttribute(Qt::WA_TransparentForMouseEvents, true);
	ui->pbtn_tranCompelete->setAttribute(Qt::WA_TransparentForMouseEvents, false);
	ui->widget_progress->move(widget_progress_rawX, widget_progress_rawY);
	ui->progress_learn->setRange(0, 100);
	ui->label_state->setText("训练中");
	ui->progress_learn->setValue(0);
	ui->txt_log->setPlainText("");
	ui->txt_log->move(txt_log_rawX, txt_log_rawY);

	//训练之前删除之前的train
	QDir dir(QString::fromStdString(PathGlobalStruct::AiLearnYoloPath) + "runs\\train");
	AiLearnTools::MoveImageToDataSet(aiLearnConfig->learnInfoSign, aiLearnConfig->checkType == 1);

	disconnect(&m_Process, &QProcess::readyRead, this, &DlgAiLearn::ProcessReadOut);//读就绪
	disconnect(&m_Process, &QProcess::readyReadStandardError, this, &DlgAiLearn::ProcessReadOut);//读就绪
	disconnect(&m_Process, &QProcess::finished, this, &DlgAiLearn::ProcessFinished);//进程完成
	connect(&m_Process, &QProcess::readyRead, this, &DlgAiLearn::ProcessReadOut);//读就绪
	connect(&m_Process, &QProcess::readyReadStandardError, this, &DlgAiLearn::ProcessReadOut);//读就绪
	connect(&m_Process, &QProcess::finished, this, &DlgAiLearn::ProcessFinished);//进程完成

	auto str = "activate yolov5 && cd /d " + PathGlobalStruct::AiLearnYoloPath + " && python train.py";
	m_Process.start("cmd.exe", { "/c",str.c_str() });
}

void DlgAiLearn::pbtn_test_clicked()
{
	std::string image_path = R"(D:\y\yolov5-master\datasets\mydataset\train\images\061812597442.jpg)";  // Windows 示例

	// 读取图片到 cv::Mat
	cv::Mat image = cv::imread(image_path, cv::IMREAD_COLOR);  // 默认以彩色模式读取

	if (ui->rbtn_station2->isChecked())
		onFrameCapturedBad(image, 2);
	else if (ui->rbtn_station3->isChecked())
		onFrameCapturedBad(image, 3);
	else if (ui->rbtn_station4->isChecked())
		onFrameCapturedBad(image, 4);
	else
		onFrameCapturedBad(image, 1);
}

void DlgAiLearn::pbtn_tranCompelete_clicked()
{
	ui->widget_progress->move(moveLen, 0);
	ui->txt_log->move(moveLen, 0);
	ui->pbtn_tranCompelete->move(moveLen, 0);
	setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void DlgAiLearn::ProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	if (exitStatus == QProcess::NormalExit)
	{
		ui->pbtn_tranCompelete->move(pbtn_tranCompelete_rawX, pbtn_tranCompelete_rawY);
		ui->label_state->setText("训练完成");
		qDebug() << "进来";
		QProcess* processRobot_1 = new QProcess();
		processRobot_1->start("cmd.exe");
		processRobot_1->write("activate yolov5");
		processRobot_1->write("&&");

		processRobot_1->write("cd /d D:\\y\\yolov5-master\\ && start python export.py\n ");
	}
	else
	{
		//程序异常结束
		qDebug() << "进来2";
	}
}

void DlgAiLearn::ProcessReadOut()
{
	auto out = m_Process.readAllStandardError();

	QRegularExpression re(R"((?<!\d)(100|[1-9]?\d)%(?!\d))");  // 带捕获组的正则
	QVector<int> results;

	QRegularExpressionMatchIterator it = re.globalMatch(out);
	while (it.hasNext()) {
		QRegularExpressionMatch match = it.next();
		results.append(
			match.captured(1).toInt()
		);
	}

	if (results.size() > 0) {
		std::sort(results.begin(), results.end());
		ui->progress_learn->setValue(results[results.length() - 1]);
	}

	auto log = QString::fromLocal8Bit(out.toStdString());
	qDebug() << log;
	ui->txt_log->appendPlainText(log);
}

