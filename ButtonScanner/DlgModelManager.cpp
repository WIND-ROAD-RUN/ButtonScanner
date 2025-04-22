#include "stdafx.h"
#include "DlgModelManager.h"

#include"ModelStorageManager.h"
#include"GlobalStruct.h"
#include"ButtonUtilty.h"

DlgModelManager::DlgModelManager(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgModelManagerClass())
{
	ui->setupUi(this);

	build_ui();
	build_connect();
}

DlgModelManager::~DlgModelManager()
{
	delete ui;
}

void DlgModelManager::build_ui()
{
	_ModelListmodel = new QStringListModel(this);
	ui->listView_modelList->setModel(_ModelListmodel);
}

void DlgModelManager::build_connect()
{
	QObject::connect(ui->pbtn_exit, &QPushButton::clicked,
		this, &DlgModelManager::pbtn_exit_clicked);
}

void DlgModelManager::pbtn_exit_clicked()
{
	this->hide();
}

void DlgModelManager::showEvent(QShowEvent* show_event)
{
	QDialog::showEvent(show_event);
	flashModelList();

}

void DlgModelManager::flashModelList()
{
	auto& globalStruct = GlobalStructData::getInstance();
	auto& modelStorageManager = globalStruct.modelStorageManager;
	_configIndex = modelStorageManager->getModelConfigIndex();

	QStringList data;
	for (const auto& item : _configIndex.modelIndexs)
	{
		QString modelTypeStr = QString::fromStdString(
			item.model_type == rw::cdm::ModelType::Undefined ? "未定义" :
			item.model_type == rw::cdm::ModelType::BladeShape ? "刀型" :
			item.model_type == rw::cdm::ModelType::Color ? "颜色" : "未知");

		data << QString::fromStdString(item.model_name) + " (" + modelTypeStr + ")";
	}

	_ModelListmodel->setStringList(data);
}
