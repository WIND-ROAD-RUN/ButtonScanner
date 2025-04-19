#include"stdafx.h"

#include"AiTrainModule.h"
#include"GlobalStruct.h"


AiTrainModule::AiTrainModule(QObject* parent)
	: QThread(parent) {

	auto enginePath = globalPath.modelRootPath + globalPath.engineFileName;
	auto namePath = globalPath.modelRootPath + globalPath.nameFileName;
	labelEngine = std::make_unique<rw::imeot::ModelEngineOT>(enginePath.toStdString(), namePath.toStdString());
}

AiTrainModule::~AiTrainModule()
{
	wait();
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
