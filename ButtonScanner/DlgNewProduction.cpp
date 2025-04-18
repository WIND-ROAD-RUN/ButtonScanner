#include "stdafx.h"
#include "DlgNewProduction.h"

#include"ButtonUtilty.h"
#include"GlobalStruct.h"
#include<QThread>
#include<QtConcurrent>

#include"imeot_ModelEngineOT.h"
#include"imest_ModelEnginest.h"

DlgNewProduction::DlgNewProduction(QWidget* parent)
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
		this, &DlgNewProduction::pbtn_tab2_check_color_clicked);
	QObject::connect(ui->pbtn_tab2_checkBladeShape, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab2_check_blade_shape_clicked);
	QObject::connect(ui->pbtn_tab2_preStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab2_pre_step_clicked);
	QObject::connect(ui->pbtn_tab2_exit, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab2_exit_clicked);
	//tab3
	QObject::connect(ui->pbtn_tab3_openImgLocate, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab3_open_img_locate_clicked);
	QObject::connect(ui->pbtn_tab3_exit, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab3_exit_clicked);
	QObject::connect(ui->pbtn_tab3_preStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab3_pre_step_clicked);
	QObject::connect(ui->pbtn_tab3_nexStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab3_nex_step_clicked);
	//tab4
	QObject::connect(ui->pbtn_tab4_openImgLocate, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab4_open_img_locate_clicked);
	QObject::connect(ui->pbtn_tab4_exit, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab4_exit_clicked);
	QObject::connect(ui->pbtn_tab4_preStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab4_pre_step_clicked);
	QObject::connect(ui->pbtn_tab4_nexStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab4_nex_step_clicked);
	//tab5
	QObject::connect(ui->pbtn_tab5_startTrain, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab5_start_train_clicked);
	QObject::connect(ui->pbtn_tab5_exit, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab5_exit_clicked);
	QObject::connect(ui->pbtn_tab5_preStep, &QPushButton::clicked,
		this, &DlgNewProduction::pbtn_tab5_pre_step_clicked);
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
	this->_info.currentTabIndex = 0;
	this->_info.isActivate = false;
	this->hide();
}

void DlgNewProduction::img_display_work1(const QPixmap& pixmap)
{
	if (pixmap.isNull())
	{
		return;
	}
	if (this->_info.currentTabIndex == 2)
	{
		ui->label_tab3_imgDisplay1->setPixmap(pixmap.scaled(ui->label_tab3_imgDisplay1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	else if (this->_info.currentTabIndex == 3)
	{
		ui->label_tab4_imgDisplay1->setPixmap(pixmap.scaled(ui->label_tab4_imgDisplay1->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
}

void DlgNewProduction::img_display_work2(const QPixmap& pixmap)
{
	if (pixmap.isNull())
	{
		return;
	}
	if (this->_info.currentTabIndex == 2)
	{
		ui->label_tab3_imgDisplay2->setPixmap(pixmap.scaled(ui->label_tab3_imgDisplay2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	else if (this->_info.currentTabIndex == 3)
	{
		ui->label_tab4_imgDisplay2->setPixmap(pixmap.scaled(ui->label_tab4_imgDisplay2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
}

void DlgNewProduction::img_display_work3(const QPixmap& pixmap)
{
	if (pixmap.isNull())
	{
		return;
	}
	if (this->_info.currentTabIndex == 2)
	{
		ui->label_tab3_imgDisplay3->setPixmap(pixmap.scaled(ui->label_tab3_imgDisplay3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	else if (this->_info.currentTabIndex == 3)
	{
		ui->label_tab4_imgDisplay3->setPixmap(pixmap.scaled(ui->label_tab4_imgDisplay3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
}

void DlgNewProduction::img_display_work4(const QPixmap& pixmap)
{
	if (pixmap.isNull())
	{
		return;
	}
	if (this->_info.currentTabIndex == 2)
	{
		ui->label_tab3_imgDisplay4->setPixmap(pixmap.scaled(ui->label_tab3_imgDisplay4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
	else if (this->_info.currentTabIndex == 3)
	{
		ui->label_tab4_imgDisplay4->setPixmap(pixmap.scaled(ui->label_tab4_imgDisplay4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}
}

void DlgNewProduction::pbtn_tab1_no_clicked()
{
	ui->tabWidget->setCurrentIndex(1);
	this->_info.currentTabIndex = 1;
}

void DlgNewProduction::pbtn_tab1_exit_clicked()
{
	destroy();
}

void DlgNewProduction::pbtn_tab2_check_color_clicked()
{
	ui->rbtn_tab3_filterColor->setChecked(true);
	ui->rbtn_tab4_filterColor->setChecked(true);
	ui->rbtn_tab5_filterColor->setChecked(true);
	this->_info.state = _info.state = DlgNewProductionInfo::CheckColor;
	ui->tabWidget->setCurrentIndex(2);
	this->_info.currentTabIndex = 2;

	auto& modelStorageManager = GlobalStructData::getInstance().modelStorageManager;
	ui->label_tab3_tabImgCount1->setText(QString::number(modelStorageManager->work1_bad_count_));
	ui->label_tab3_tabImgCount2->setText(QString::number(modelStorageManager->work2_bad_count_));
	ui->label_tab3_tabImgCount3->setText(QString::number(modelStorageManager->work3_bad_count_));
	ui->label_tab3_tabImgCount4->setText(QString::number(modelStorageManager->work4_bad_count_));
}

void DlgNewProduction::pbtn_tab2_check_blade_shape_clicked()
{
	ui->rbtn_tab3_filterColor->setChecked(false);
	ui->rbtn_tab4_filterColor->setChecked(false);
	ui->rbtn_tab5_filterColor->setChecked(false);
	ui->rbtn_tab3_checkBladeShape->setChecked(true);
	ui->rbtn_tab4_checkBladeShape->setChecked(true);
	ui->rbtn_tab5_checkBladeShape->setChecked(true);
	this->_info.state = _info.state = DlgNewProductionInfo::CheckBladeShape;
	ui->tabWidget->setCurrentIndex(2);
	this->_info.currentTabIndex = 2;

	auto& modelStorageManager = GlobalStructData::getInstance().modelStorageManager;
	ui->label_tab3_tabImgCount1->setText(QString::number(modelStorageManager->work1_bad_count_));
	ui->label_tab3_tabImgCount2->setText(QString::number(modelStorageManager->work2_bad_count_));
	ui->label_tab3_tabImgCount3->setText(QString::number(modelStorageManager->work3_bad_count_));
	ui->label_tab3_tabImgCount4->setText(QString::number(modelStorageManager->work4_bad_count_));
}

void DlgNewProduction::pbtn_tab2_pre_step_clicked()
{
	ui->tabWidget->setCurrentIndex(0);
	this->_info.currentTabIndex = 0;
}

void DlgNewProduction::pbtn_tab2_exit_clicked()
{
	destroy();
}

void DlgNewProduction::pbtn_tab3_open_img_locate_clicked()
{
}

void DlgNewProduction::pbtn_tab3_exit_clicked()
{
	destroy();
}

void DlgNewProduction::pbtn_tab3_pre_step_clicked()
{
	ui->tabWidget->setCurrentIndex(1);
	this->_info.currentTabIndex = 1;
	this->_info.state = _info.state = DlgNewProductionInfo::None;
	ui->rbtn_tab3_filterColor->setChecked(false);
	ui->rbtn_tab4_filterColor->setChecked(false);
	ui->rbtn_tab5_filterColor->setChecked(false);
	ui->rbtn_tab3_checkBladeShape->setChecked(true);
	ui->rbtn_tab4_checkBladeShape->setChecked(true);
	ui->rbtn_tab5_checkBladeShape->setChecked(true);
}

void DlgNewProduction::pbtn_tab3_nex_step_clicked()
{
	ui->tabWidget->setCurrentIndex(3);
	this->_info.currentTabIndex = 3;

	auto& modelStorageManager = GlobalStructData::getInstance().modelStorageManager;
	ui->label_tab4_tabImgCount1->setText(QString::number(modelStorageManager->work1_good_count_));
	ui->label_tab4_tabImgCount2->setText(QString::number(modelStorageManager->work2_good_count_));
	ui->label_tab4_tabImgCount3->setText(QString::number(modelStorageManager->work3_good_count_));
	ui->label_tab4_tabImgCount4->setText(QString::number(modelStorageManager->work4_good_count_));
}

void DlgNewProduction::pbtn_tab4_open_img_locate_clicked()
{
}

void DlgNewProduction::pbtn_tab4_exit_clicked()
{
	destroy();
}

void DlgNewProduction::pbtn_tab4_pre_step_clicked()
{
	ui->tabWidget->setCurrentIndex(2);
	this->_info.currentTabIndex = 2;
}

void DlgNewProduction::pbtn_tab4_nex_step_clicked()
{
	ui->tabWidget->setCurrentIndex(4);
	this->_info.currentTabIndex = 4;
}

void DlgNewProduction::pbtn_tab5_start_train_clicked()
{
	auto & aiTrainModule = GlobalStructThread::getInstance().aiTrainModule;
	if (this->_info.state== DlgNewProductionInfo::CheckBladeShape)
	{
		aiTrainModule->setModelType(ModelType::ObejectDetection);
	}
	else if (this->_info.state == DlgNewProductionInfo::CheckColor)
	{
		aiTrainModule->setModelType(ModelType::Segment);
	}
	else
	{
		return;
	}
	aiTrainModule->startTrain();
}

void DlgNewProduction::pbtn_tab5_exit_clicked()
{
	destroy();
}

void DlgNewProduction::pbtn_tab5_pre_step_clicked()
{
	ui->tabWidget->setCurrentIndex(3);
	this->_info.currentTabIndex = 3;
}

void DlgNewProduction::pbtn_tab5_finish_clicked()
{
	destroy();
}

void DlgNewProduction::showEvent(QShowEvent* show_event)
{
	this->_info.isActivate = true;
	QDialog::showEvent(show_event);
}

void DlgNewProduction::appendAiTrainLog(QString log)
{
	if (log.isEmpty())
	{
		return;
	}
	ui->plainTextEdit_tab5->appendPlainText(log);
}

void DlgNewProduction::img_display_work(cv::Mat frame, size_t index)
{
	if (_info.isActivate == false)
	{
		return;
	}
	if ((_info.currentTabIndex != 2) && (_info.currentTabIndex != 3))
	{
		return;
	}
	auto pixmap = cvMatToQPixmap(frame);
	switch (index)
	{
	case 1:
		img_display_work1(pixmap);
		break;
	case 2:
		img_display_work2(pixmap);
		break;
	case 3:
		img_display_work3(pixmap);
		break;
	case 4:
		img_display_work4(pixmap);
		break;
	default:
		break;
	}
}

void DlgNewProduction::pbtn_tab1_ok_clicked()
{
	auto result = QMessageBox::question(this, "确定", "你确定要清除所有文件吗");
	if (result == QMessageBox::Yes)
	{
		auto& globalStruct = GlobalStructData::getInstance();
		globalStruct.modelStorageManager->clear_temp();
		ui->tabWidget->setCurrentIndex(1);
		this->_info.currentTabIndex = 1;
	}
	else
	{
		return;
	}
}