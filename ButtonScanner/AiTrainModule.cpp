#include"stdafx.h"

#include"AiTrainModule.h"
#include"GlobalStruct.h"


AiTrainModule::AiTrainModule(QObject* parent)
	: QThread(parent) {

	auto enginePath = globalPath.modelRootPath + globalPath.engineFileName;
	auto namePath = globalPath.modelRootPath + globalPath.nameFileName;
	labelEngine = std::make_unique<rw::imeot::ModelEngineOT>(enginePath.toStdString(), namePath.toStdString());
	_process = new QProcess();
	connect(_process, &QProcess::readyReadStandardOutput, this, &AiTrainModule::handleProcessOutput);
	connect(_process, &QProcess::readyReadStandardError, this, &AiTrainModule::handleProcessError);
	connect(_process, &QProcess::finished, this, &AiTrainModule::handleProcessFinished);
}

AiTrainModule::~AiTrainModule()
{
	wait();
	delete _process;
}

void AiTrainModule::startTrain()
{
	start();
}

rw::imeot::ProcessRectanglesResultOT AiTrainModule::getBody(
	std::vector<rw::imeot::ProcessRectanglesResultOT>& processRectanglesResult, bool& hasBody)
{
	hasBody = false;
	rw::imeot::ProcessRectanglesResultOT result;
	result.width = 0;
	result.height = 0;
	for (auto& i : processRectanglesResult)
	{
		if (i.classID == 0)
		{
			if ((i.width * i.height) > (result.width * result.height))
			{
				result = i;
				hasBody = true;
			}
		}
	}
	return result;
}

QVector<AiTrainModule::DataItem> AiTrainModule::getDataSet(const QVector<labelAndImg>& annotationDataSet, ModelType type, int classId)
{
	QVector<AiTrainModule::DataItem> result;
	switch (type)
	{
	case ModelType::Segment:
		result = getSegmentDataSet(annotationDataSet, classId);
		break;
	case ModelType::ObejectDetection:
		result = getObjectDetectionDataSet(annotationDataSet, classId);
		break;
	default:
		break;
	}
	return result;

}

QVector<AiTrainModule::DataItem> AiTrainModule::getSegmentDataSet(const QVector<labelAndImg>& annotationDataSet, int classId)
{
	QVector<AiTrainModule::DataItem> result;
	for (const auto& item : annotationDataSet)
	{
		std::string id = classId ==0 ? "0" : "1";
		//normalization归一化

		double norCenterX = static_cast<double>(item.second.center_x) / static_cast<double>(_framWidth);
		double norCenterY = static_cast<double>(item.second.center_y) / static_cast<double>(_frameHeight);
		double norWidth = static_cast<double>(item.second.width) / static_cast<double>(_framWidth);
		double norHeight = static_cast<double>(item.second.height) / static_cast<double>(_frameHeight);

		auto textStr = id + " " +
			std::to_string(norCenterX) + " " + std::to_string(norCenterY) + " "
			+ std::to_string(norWidth) + " " + std::to_string(norHeight);

		using Point = std::pair<double, double>;
		std::vector< Point> points;
		points.reserve(31);

		double angleStep = 2 * M_PI / 30;

		//算出半径
		auto r = (norHeight + (norWidth - norHeight) / 2) / 2;

		for (int i = 0; i < 30; i++) {
			double theta = i * angleStep;
			double x = norCenterX + r * std::cos(theta);
			double y = norCenterY + r * std::sin(theta);
			points.push_back(Point{ x, y });
		}
		points.push_back(points[0]);

		textStr += " ";
		for (int i = 0; i < 31; i++) {
			textStr += std::to_string(points[i].first) + "_" + std::to_string(points[i].second);
			if (i != 30)
				textStr += ",";
		}
		result.append({ item.first, QString::fromStdString(textStr) });
	}
	return result;
}


QVector<AiTrainModule::DataItem> AiTrainModule::getObjectDetectionDataSet(const QVector<labelAndImg>& annotationDataSet, int classId)
{
	QVector<AiTrainModule::DataItem> result;
	for (const auto& item : annotationDataSet)
	{
		std::string id = std::to_string(classId);
		//normalization归一化

		double norCenterX = static_cast<double>(item.second.center_x) / static_cast<double>(_framWidth);
		double norCenterY = static_cast<double>(item.second.center_y) / static_cast<double>(_frameHeight);
		double norWidth = static_cast<double>(item.second.width) / static_cast<double>(_framWidth);
		double norHeight = static_cast<double>(item.second.height) / static_cast<double>(_frameHeight);

		auto textStr = id + " " +
			std::to_string(norCenterX) + " " + std::to_string(norCenterY) + " "
			+ std::to_string(norWidth) + " " + std::to_string(norHeight);

		
		result.append({ item.first, QString::fromStdString(textStr) });
	}
	return result;
}

void AiTrainModule::clear_older_trainData()
{
	QString workPlace = globalPath.yoloV5RootPath;
	QDir dir(workPlace);
	QString absolutePath = dir.absolutePath();

	// 处理 Run 目录
	{
		QString runDir = workPlace + R"(runs\)";
		QString trainDir = runDir + R"(train\)";
		QString trainSeg = runDir + R"(train-seg\)";

		// 删除 trainDir 及其所有子文件和子文件夹
		QDir trainDirObj(trainDir);
		if (trainDirObj.exists()) {
			trainDirObj.removeRecursively();
		}

		// 删除 trainSeg 及其所有子文件和子文件夹
		QDir trainSegObj(trainSeg);
		if (trainSegObj.exists()) {
			trainSegObj.removeRecursively();
		}
	}

	// 处理 dataset 目录
	{
		QString dataSetDir = workPlace + R"(datasets\mydataset)";
		QString trainDir = dataSetDir + R"(\train\)";
		QString valDir = dataSetDir + R"(\val\)";
		QString testDir = dataSetDir + R"(\tes\)";

		// 删除 trainDir 及其所有子文件和子文件夹
		QDir trainDirObj(trainDir);
		if (trainDirObj.exists()) {
			trainDirObj.removeRecursively();
		}

		// 删除 valDir 及其所有子文件和子文件夹
		QDir valDirObj(valDir);
		if (valDirObj.exists()) {
			valDirObj.removeRecursively();
		}

		// 删除 testDir 及其所有子文件和子文件夹
		QDir testDirObj(testDir);
		if (testDirObj.exists()) {
			testDirObj.removeRecursively();
		}
	}

	//处理segDatasets
	{
		QString segDataSetDir = workPlace + R"(segDatasets\mydataset)";
		QString trainDir = segDataSetDir + R"(\train\)";
		QString valDir = segDataSetDir + R"(\val\)";
		QString testDir = segDataSetDir + R"(\tes\)";
		// 删除 trainDir 及其所有子文件和子文件夹
		QDir trainDirObj(trainDir);
		if (trainDirObj.exists()) {
			trainDirObj.removeRecursively();
		}
		// 删除 valDir 及其所有子文件和子文件夹
		QDir valDirObj(valDir);
		if (valDirObj.exists()) {
			valDirObj.removeRecursively();
		}
		// 删除 testDir 及其所有子文件和子文件夹
		QDir testDirObj(testDir);
		if (testDirObj.exists()) {
			testDirObj.removeRecursively();
		}
	}
	

}

void AiTrainModule::copyTrainData(const QVector<AiTrainModule::DataItem>& dataSet)
{
	if (_modelType == ModelType::ObejectDetection)
	{
		copyTrainImgData(dataSet, QString(globalPath.yoloV5RootPath + R"(\datasets\mydataset\tes\)"));
		copyTrainImgData(dataSet, QString(globalPath.yoloV5RootPath + R"(\datasets\mydataset\train\images\)"));
		copyTrainImgData(dataSet, QString(globalPath.yoloV5RootPath + R"(\datasets\mydataset\val\images\)"));

		copyTrainLabelData(dataSet, QString(globalPath.yoloV5RootPath + R"(\datasets\mydataset\train\labels)"));
		copyTrainLabelData(dataSet, QString(globalPath.yoloV5RootPath + R"(\datasets\mydataset\val\labels)"));
	}
	else if (_modelType == ModelType::Segment)
	{
		copyTrainImgData(dataSet, QString(globalPath.yoloV5RootPath + R"(\segdatasets\mydataset\tes\)"));
		copyTrainImgData(dataSet, QString(globalPath.yoloV5RootPath + R"(\segdatasets\mydataset\train\images\)"));
		copyTrainImgData(dataSet, QString(globalPath.yoloV5RootPath + R"(\segdatasets\mydataset\val\images\)"));

		copyTrainLabelData(dataSet, QString(globalPath.yoloV5RootPath + R"(\segdatasets\mydataset\train\labels)"));
		copyTrainLabelData(dataSet, QString(globalPath.yoloV5RootPath + R"(\segdatasets\mydataset\val\labels)"));
	}
}

void AiTrainModule::copyTrainImgData(const QVector<AiTrainModule::DataItem>& dataSet, const QString& path)
{
	// 检查目标路径是否存在，如果不存在则创建
	QDir dir(path);
	if (!dir.exists()) {
		if (!dir.mkpath(path)) {
			emit appRunLog("Failed to create directory: " + path);
			return;
		}
	}

	// 遍历 dataSet 并拷贝图片
	for (const auto& item : dataSet) {
		QString sourcePath = item.first; // 图片的源路径
		QString fileName = QFileInfo(sourcePath).fileName(); // 获取文件名
		QString destinationPath = path + QDir::separator() + fileName; // 目标路径

		// 拷贝文件
		if (!QFile::copy(sourcePath, destinationPath)) {
			emit appRunLog("Failed to copy file: " + sourcePath + " to " + destinationPath);
		}
		else {
			emit appRunLog("Copied file: " + sourcePath + " to " + destinationPath);
		}
	}
}

void AiTrainModule::copyTrainLabelData(const QVector<AiTrainModule::DataItem>& dataSet, const QString& path)
{
	// 检查目标路径是否存在，如果不存在则创建
	QDir dir(path);
	if (!dir.exists()) {
		if (!dir.mkpath(path)) {
			emit appRunLog("Failed to create directory: " + path);
			return;
		}
	}

	// 遍历 dataSet 并保存 label 数据
	for (const auto& item : dataSet) {
		QString fileName = QFileInfo(item.first).baseName() + ".txt"; // 获取文件名并添加 .txt 后缀
		QString filePath = path + QDir::separator() + fileName; // 目标文件路径

		QFile file(filePath);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream out(&file);
			out << item.second; // 写入 label 数据
			file.close();
			emit appRunLog("Saved label file: " + filePath);
		}
		else {
			emit appRunLog("Failed to save label file: " + filePath);
		}
	}
}

void AiTrainModule::trainSegmentModel()
{

}

void AiTrainModule::trainObbModel()
{
	auto str = "activate yolov5 && cd /d " + globalPath.yoloV5RootPath.toStdString() + " && python train.py";
	_process->start("cmd.exe", { "/c",str.c_str() });
}

cv::Mat AiTrainModule::getMatFromPath(const QString& path)
{
	cv::Mat image = cv::imread(path.toStdString());
	if (image.empty()) {
		qDebug() << "Failed to load image:" << path;
	}
	return image;
}

void AiTrainModule::run()
{
	emit appRunLog("训练启动....");

	emit appRunLog("清理旧的训练数据....");
	clear_older_trainData();

	//获取图片的label
	auto annotationGoodDataSet = annotation_data_set(false);
	auto annotationBadDataSet = annotation_data_set(true);
	auto dataSet = getDataSet(annotationGoodDataSet, _modelType, 1);
	auto dataSetBad = getDataSet(annotationBadDataSet, _modelType, 0);
	QString GoodSetLog = "其中正确的纽扣数据集有" + QString::number(dataSet.size()) + "条数据";
	QString BadSetLog = "其中错误的纽扣数据集有" + QString::number(dataSetBad.size()) + "条数据";
	emit appRunLog(GoodSetLog);
	emit appRunLog(BadSetLog);

	//拷贝训练数据
	emit appRunLog("拷贝训练文件");
	copyTrainData(dataSet);
	copyTrainData(dataSetBad);

	if (_modelType==ModelType::Segment)
	{
		emit appRunLog("开始训练分割模型");
		trainSegmentModel();
	}
	else if (_modelType == ModelType::ObejectDetection)
	{
		emit appRunLog("开始训练检测模型");
		trainObbModel();
	}

	exec();
}

QVector<AiTrainModule::labelAndImg> AiTrainModule::annotation_data_set(bool isBad)
{
	QVector<QString> imageList ;
	if (isBad)
	{
		emit appRunLog("正在标注要筛选的纽扣数据集");
		imageList = GlobalStructData::getInstance().modelStorageManager->getBadImagePathList();
	}
	else
	{
		emit appRunLog("正在标注正确的纽扣的数据集");
		imageList = GlobalStructData::getInstance().modelStorageManager->getGoodImagePathList();
	}
	
	int i = 0;

	QVector<labelAndImg> dataSet;
	dataSet.reserve(100);

	//获取图片的label
	for (const auto& imagePath : imageList) {
		auto image = getMatFromPath(imagePath);
		if (image.empty()) {
			continue;
		}
		_framWidth = image.cols;
		_frameHeight = image.rows;
		cv::Mat resultMat;
		std::vector<rw::imeot::ProcessRectanglesResultOT> result;
		labelEngine->ProcessMask(image, resultMat, result);
		QString log = QString::number(i) + " ";

		bool hasBody;
		auto body = getBody(result, hasBody);
		if (!hasBody)
		{
			continue;
		}

		dataSet.emplaceBack(imagePath, body);
		log += "ClassId: " + QString::number(body.classID) + " center_x" + QString::number(body.center_x) + " center_y" + QString::number(body.center_y);
		emit appRunLog(log);
		i++;
	}
	emit appRunLog("标注完" + QString::number(dataSet.size()) + "条数据");

	return dataSet;
}

void AiTrainModule::handleProcessOutput()
{
	QByteArray output = _process->readAllStandardOutput();
	QString outputStr = QString::fromLocal8Bit(output);
	emit appRunLog(outputStr); // 将输出内容发送到日志或界面
}

void AiTrainModule::handleProcessError()
{
	QByteArray errorOutput = _process->readAllStandardError();
	QString errorStr = QString::fromLocal8Bit(errorOutput);
	emit appRunLog(errorStr); // 将错误内容发送到日志或界面
}

void AiTrainModule::handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	if (exitStatus == QProcess::NormalExit)
	{

	}
	else
	{
		//程序异常结束
		qDebug() << "进来2";
	}

	quit();
}

