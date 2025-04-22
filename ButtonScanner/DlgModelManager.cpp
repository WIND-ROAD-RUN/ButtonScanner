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

	// 设置 QListView 的样式表，调整项的高度和字体大小
	ui->listView_modelList->setStyleSheet(
		"QListView::item {"
		"   height: 50px;" // 设置项的高度
		"   font-size: 18px;" // 设置字体大小
		"}"
	);
}

void DlgModelManager::build_connect()
{
	QObject::connect(ui->pbtn_exit, &QPushButton::clicked,
		this, &DlgModelManager::pbtn_exit_clicked);
	QObject::connect(ui->listView_modelList->selectionModel(), &QItemSelectionModel::currentChanged,
		this, &DlgModelManager::onModelListSelectionChanged);

}

void DlgModelManager::pbtn_exit_clicked()
{
	this->hide();
}

void DlgModelManager::onModelListSelectionChanged(const QModelIndex& current, const QModelIndex& previous)

{
	// 检查当前索引是否有效
	if (!current.isValid()) {
		return;
	}

	// 获取当前选择的模型索引
	int selectedIndex = current.row();

	// 刷新模型信息表和示例图片
	flashModelInfoTable(selectedIndex);
	flashExampleImage(selectedIndex);
}

void DlgModelManager::showEvent(QShowEvent* show_event)
{
	QDialog::showEvent(show_event);
	flashModelList();
	flashModelInfoTable(0);
	flashExampleImage(0);

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

QVector<QString> DlgModelManager::getImagePaths(const QString& rootPath, bool isGood)
{
	QVector<QString> imagePaths;
	QString rootImagePath = rootPath + "/Image/";
	QDir rootDir(rootImagePath);

	if (!rootDir.exists()) {
		qDebug() << "根路径不存在:" << rootImagePath;
		return imagePaths;
	}

	// 定义目标文件夹名称
	QString targetFolder = isGood ? "good" : "bad";

	// 遍历 work1, work2, work3, work4 文件夹
	QStringList workFolders = rootDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	for (const QString& workFolder : workFolders) {
		QDir workDir(rootDir.filePath(workFolder));
		QDir targetDir(workDir.filePath(targetFolder));

		if (!targetDir.exists()) {
			qDebug() << "目标文件夹不存在:" << targetDir.absolutePath();
			continue;
		}

		// 查找目标文件夹下的所有 .png 文件
		QStringList filters;
		filters << "*.png";
		QStringList pngFiles = targetDir.entryList(filters, QDir::Files | QDir::NoSymLinks);

		// 获取每个文件的绝对路径并添加到结果中
		for (const QString& pngFile : pngFiles) {
			imagePaths.append(targetDir.absoluteFilePath(pngFile));
		}
	}

	return imagePaths;
}

QVector<QString> DlgModelManager::getImagePaths(const QString& rootPath, bool isGood, int maxCount)
{
	QVector<QString> imagePaths;
	QString rootImagePath = rootPath + "/Image/";
	QDir rootDir(rootImagePath);

	if (!rootDir.exists()) {
		qDebug() << "根路径不存在:" << rootImagePath;
		return imagePaths;
	}

	// 定义目标文件夹名称
	QString targetFolder = isGood ? "good" : "bad";

	// 遍历 work1, work2, work3, work4 文件夹
	QStringList workFolders = rootDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	for (const QString& workFolder : workFolders) {
		QDir workDir(rootDir.filePath(workFolder));
		QDir targetDir(workDir.filePath(targetFolder));

		if (!targetDir.exists()) {
			qDebug() << "目标文件夹不存在:" << targetDir.absolutePath();
			continue;
		}

		// 查找目标文件夹下的所有 .png 文件
		QStringList filters;
		filters << "*.png";
		QStringList pngFiles = targetDir.entryList(filters, QDir::Files | QDir::NoSymLinks);

		// 获取每个文件的绝对路径并添加到结果中
		for (const QString& pngFile : pngFiles) {
			imagePaths.append(targetDir.absoluteFilePath(pngFile));

			// 如果已找到指定数量的图片，停止搜索
			if (imagePaths.size() >= maxCount) {
				return imagePaths;
			}
		}
	}

	return imagePaths;
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
	_modelConfigs.clear();
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

		auto configPath = findXmlFile(QString::fromStdString(item.root_path));
		if (configPath.isEmpty())
		{
			QMessageBox::warning(this, "警告", QString::fromStdString(item.root_path)+"模型配置文件不存在");
			rw::cdm::AiModelConfig aiModelConfig;
			_modelConfigs.push_back(aiModelConfig);
			continue;
		}
		auto config = globalStruct.storeContext->load(configPath.toStdString());
		rw::cdm::AiModelConfig aiModelConfig(*config);
		_modelConfigs.push_back(aiModelConfig);
	}

	_ModelListModel->setStringList(data);

	if (!_ModelListModel->stringList().isEmpty())
	{
		QModelIndex firstIndex = _ModelListModel->index(0, 0); // 获取第一个项的索引
		ui->listView_modelList->setCurrentIndex(firstIndex);   // 设置为当前选择项
	}
}


void DlgModelManager::flashModelInfoTable(size_t index)
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

	if (_configIndex.modelIndexs.size()<=index)
	{
		return;
	}
	rw::cdm::AiModelConfig aiModelConfig = _modelConfigs.at(index);

	QStandardItem* nameItem = new QStandardItem();
	nameItem->setText(QString::fromStdString(aiModelConfig.name));
	_ModelInfoModel->setItem(0, 0, nameItem);

	QStandardItem* idItem = new QStandardItem();
	idItem->setText(QString::number(aiModelConfig.id));
	_ModelInfoModel->setItem(1, 0, idItem);

	QStandardItem* modelTypeItem = new QStandardItem();
	modelTypeItem->setText(QString::fromStdString(
		aiModelConfig.modelType == rw::cdm::ModelType::Undefined ? "未定义" :
		aiModelConfig.modelType == rw::cdm::ModelType::BladeShape ? "刀型" :
		aiModelConfig.modelType == rw::cdm::ModelType::Color ? "颜色" : "未知"));
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
	rootPathItem->setText(QString::fromStdString(aiModelConfig.rootPath));
	_ModelInfoModel->setItem(8, 0, rootPathItem);

	QStandardItem* dateItem = new QStandardItem();
	dateItem->setText(formatDateString(aiModelConfig.date));
	_ModelInfoModel->setItem(9, 0, dateItem);

	ui->tableView_modelInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
	ui->tableView_modelInfo->horizontalHeader()->hide();
}

void DlgModelManager::flashExampleImage(size_t index)
{
	if (_configIndex.modelIndexs.size() <= index)
	{
		return;
	}
	auto& config = _modelConfigs.at(index);
	auto& rootPath = config.rootPath;
	auto goodImageList=getImagePaths(QString::fromStdString(rootPath),true,1);
	auto badImageList = getImagePaths(QString::fromStdString(rootPath), false,1);

	if (goodImageList.size()==0)
	{
		ui->label_imgDisplayOK->setText("未找到图片");
	}
	else
	{
		QPixmap image(goodImageList.at(0));
		ui->label_imgDisplayOK->setPixmap(image.scaled(ui->label_imgDisplayOK->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}

	if (badImageList.size()==0)
	{
		ui->label_imgDisplayNG->setText("未找到图片");
	}
	else
	{
		QPixmap image(badImageList.at(0));
		ui->label_imgDisplayNG->setPixmap(image.scaled(ui->label_imgDisplayNG->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	}

}
