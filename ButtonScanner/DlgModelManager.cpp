#include "stdafx.h"
#include "DlgModelManager.h"

#include"ModelStorageManager.h"
#include"GlobalStruct.h"
#include"ButtonUtilty.h"

DlgModelManager::DlgModelManager(QWidget* parent)
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
	_ModelListModel = new QStringListModel(this);
	ui->listView_modelList->setModel(_ModelListModel);

	_ModelInfoModel = new QStandardItemModel(this);
	ui->tableView_modelInfo->setModel(_ModelInfoModel);
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
	falshModelInfoTabel();

}

QString DlgModelManager::formatDateString(const std::string& dateStr)
{
	// 将 std::string 转换为 QString
	QString dateString = QString::fromStdString(dateStr);

	// 使用 QDateTime 解析日期字符串
	QDateTime dateTime = QDateTime::fromString(dateString, "yyyyMMddHHmmss");

	// 检查解析是否成功
	if (dateTime.isValid()) {
		// 格式化为 "2025年4月22日6时7分1秒" 的形式
		return dateTime.toString("yyyy年M月d日H时m分s秒");
	}
	else {
		// 如果解析失败，返回提示信息
		return QString::fromStdString(dateStr);
	}
}

QString DlgModelManager::findXmlFile(const QString& rootPath)
{
	// 检查路径是否有效
	QDir dir(rootPath);
	if (!dir.exists()) {
		qDebug() << "路径不存在:" << rootPath;
		return QString(); // 返回空路径
	}

	// 设置过滤器，只查找 .xml 文件
	QStringList filters;
	filters << "*.xml";

	// 获取所有匹配的文件
	QStringList xmlFiles = dir.entryList(filters, QDir::Files | QDir::NoSymLinks);

	// 如果找到文件，返回第一个文件的绝对路径
	if (!xmlFiles.isEmpty()) {
		QString absolutePath = dir.absoluteFilePath(xmlFiles.first());
		return absolutePath;
	}

	return QString();
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

	_ModelListModel->setStringList(data);

	if (!_ModelListModel->stringList().isEmpty())
	{
		QModelIndex firstIndex = _ModelListModel->index(0, 0); // 获取第一个项的索引
		ui->listView_modelList->setCurrentIndex(firstIndex);   // 设置为当前选择项
	}
}


void DlgModelManager::falshModelInfoTabel()
{
	_ModelInfoModel->clear();
	// 原始的列标题
	QStringList originalHeaders = QStringList() << "模型名称:" << "ID:" << "模型类型:" << "上光源:"
		<< "侧光源:" << "下光源:" << "曝光:"
		<< "增益:" << "模型根路径:" << "训练日期:";

	// 设置旋转后的行标题（原始列标题变为行标题）
	_ModelInfoModel->setVerticalHeaderLabels(originalHeaders);

	// 设置第一列无标题
	_ModelInfoModel->setHeaderData(0, Qt::Horizontal, QVariant()); // 清空第一列的标题

	if (_configIndex.modelIndexs.size() == 0)
	{
		return;
	}

	auto modelInfo = _configIndex.modelIndexs[0];
	auto configPath = findXmlFile(QString::fromStdString(modelInfo.root_path));
	auto& globalStruct = GlobalStructData::getInstance();
	auto config = globalStruct.storeContext->load(configPath.toStdString());
	rw::cdm::AiModelConfig aiModelConfig(*config);

	QStandardItem* nameItem = new QStandardItem();
	nameItem->setText(QString::fromStdString(aiModelConfig.name));
	_ModelInfoModel->setItem(0, 0, nameItem);

	QStandardItem* idItem = new QStandardItem();
	idItem->setText(QString::number(modelInfo.id));
	_ModelInfoModel->setItem(1, 0, idItem);

	QStandardItem* modelTypeItem = new QStandardItem();
	modelTypeItem->setText(QString::fromStdString(
		modelInfo.model_type == rw::cdm::ModelType::Undefined ? "未定义" :
		modelInfo.model_type == rw::cdm::ModelType::BladeShape ? "刀型" :
		modelInfo.model_type == rw::cdm::ModelType::Color ? "颜色" : "未知"));
	_ModelInfoModel->setItem(2, 0, modelTypeItem);

	QStandardItem* upLightItem = new QStandardItem();
	upLightItem->setText(aiModelConfig.upLight ? "开启" : "关闭");
	_ModelInfoModel->setItem(3, 0, upLightItem);

	QStandardItem* sideLightItem = new QStandardItem();
	sideLightItem->setText(aiModelConfig.sideLight ? "开启" : "关闭");
	_ModelInfoModel->setItem(4, 0, sideLightItem);

	QStandardItem* downLightItem = new QStandardItem();
	downLightItem->setText(aiModelConfig.downLight ? "开启" : "关闭");
	_ModelInfoModel->setItem(5, 0, downLightItem);

	QStandardItem* exposureItem = new QStandardItem();
	exposureItem->setText(QString::number(aiModelConfig.exposureTime));
	_ModelInfoModel->setItem(6, 0, exposureItem);

	QStandardItem* gainItem = new QStandardItem();
	gainItem->setText(QString::number(aiModelConfig.gain));
	_ModelInfoModel->setItem(7, 0, gainItem);

	QStandardItem* rootPathItem = new QStandardItem();
	rootPathItem->setText(QString::fromStdString(modelInfo.root_path));
	_ModelInfoModel->setItem(8, 0, rootPathItem);

	QStandardItem* dateItem = new QStandardItem();
	dateItem->setText(formatDateString(aiModelConfig.date));
	_ModelInfoModel->setItem(9, 0, dateItem);

	ui->tableView_modelInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	ui->tableView_modelInfo->horizontalHeader()->hide();
}