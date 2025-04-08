#include"stdafx.h"
#include "GlobalStruct.h"
#include"ImageProcessorModule.h"

void ImageProcessor::buildModelEngine(const QString& enginePath, const QString& namePath)
{
	_modelEnginePtr = std::make_unique<rw::ime::ModelEngine>(enginePath.toStdString(), namePath.toStdString());
}

cv::Mat ImageProcessor::processAI(MatInfo& frame, QVector<QString>& errorInfo)
{
	auto& globalStruct = GlobalStruct::getInstance();

	auto  systemConfig = &globalStruct.dlgProduceLineSetConfig;
	auto  checkConfig = &globalStruct.dlgProductSetConfig;
	double pixEquivalent = systemConfig->pixelEquivalent1;
	switch (frame.index)
	{
	case 2:
		pixEquivalent = systemConfig->pixelEquivalent2;
		break;
	case 3:
		pixEquivalent = systemConfig->pixelEquivalent3;
		break;
	case 4:
		pixEquivalent = systemConfig->pixelEquivalent4;
		break;
	default:
		break;
	}


	cv::Mat resultImage;
	cv::Mat maskImage = cv::Mat::zeros(frame.image.size(), CV_8UC1);
	std::vector<rw::ime::ProcessRectanglesResult> vecRecogResult;
	double t = (double)cv::getTickCount();

	// Process the frame
	_modelEnginePtr->ProcessMask(frame.image, resultImage, maskImage, vecRecogResult);

	auto isBad = false;

	std::vector<rw::ime::ProcessRectanglesResult> vecrecogresult;
	cv::Mat resultMat;
	cv::Mat maskmat;

	std::vector<int> waiJingIndexs = std::vector<int>();
	std::vector<int> konJingIndexs = std::vector<int>();
	std::vector<int> daPoBianIndexs = std::vector<int>();
	std::vector<int> qiKonIndexs = std::vector<int>();
	std::vector<int> duYanIndexs = std::vector<int>();
	std::vector<int> moShiIndexs = std::vector<int>();
	std::vector<int> liaoTouIndexs = std::vector<int>();
	std::vector<int> youQiIndexs = std::vector<int>();
	std::vector<int> lieHenIndexs = std::vector<int>();
	std::vector<int> poYanIndexs = std::vector<int>();

	for (int i = 0; i < vecrecogresult.size(); i++)
	{
		switch (vecrecogresult[i].classId)
		{
		case 0: waiJingIndexs.push_back(i); continue;
		case 1: konJingIndexs.push_back(i); continue;
		case 2: daPoBianIndexs.push_back(i); continue;
		case 3: qiKonIndexs.push_back(i); continue;
		case 4: duYanIndexs.push_back(i); continue;
		case 5: moShiIndexs.push_back(i); continue;
		case 6: liaoTouIndexs.push_back(i); continue;
		case 7: youQiIndexs.push_back(i); continue;
		case 8: lieHenIndexs.push_back(i); continue;
		case 9: poYanIndexs.push_back(i); continue;

		default: continue;
		}
	}


	if (checkConfig->outsideDiameterEnable)
		if (waiJingIndexs.size() == 0)
		{
			isBad = true;
			errorInfo.emplace_back("没找到外径");
		}
		else
		{
			auto shangXiaPianCha = vecrecogresult[waiJingIndexs[0]].right_bottom.second - vecrecogresult[waiJingIndexs[0]].left_top.second - checkConfig->outsideDiameterValue / pixEquivalent;
			auto zuoYouPianCha = vecrecogresult[waiJingIndexs[0]].right_bottom.first - vecrecogresult[waiJingIndexs[0]].left_top.first - checkConfig->outsideDiameterValue / pixEquivalent;

			auto shangXiaPianChaAbs = abs(shangXiaPianCha);
			auto zuoYouPianChaAbs = abs(zuoYouPianCha);

			if (shangXiaPianChaAbs > checkConfig->outsideDiameterDeviation / pixEquivalent || zuoYouPianChaAbs > checkConfig->outsideDiameterDeviation / pixEquivalent)
			{
				isBad = true;

				if (shangXiaPianChaAbs >= zuoYouPianChaAbs)
					errorInfo.emplace_back("外径 "+QString::number(shangXiaPianCha * CameraSetting()->xiangShuDangLiang));
				else
					errorInfo.emplace_back("外径 " + QString::number(zuoYouPianCha * CameraSetting()->xiangShuDangLiang));
			}
		}

	if (checkConfig->holesCountEnable)
		if (konJingIndexs.size() != checkConfig->holesCountValue)
		{
			isBad = true;
			errorInfo.emplace_back("只找到" + QString::number(konJingIndexs.size()) + "个孔");
		}

	if (checkConfig->apertureEnable)
		for (int i = 0; i < konJingIndexs.size(); i++)
		{
			auto shangXiaPianCha = vecrecogresult[konJingIndexs[i]].right_bottom.second - vecrecogresult[konJingIndexs[i]].left_top.second - checkConfig->apertureValue / pixEquivalent;
			auto zuoYouPianCha = vecrecogresult[konJingIndexs[i]].right_bottom.first - vecrecogresult[konJingIndexs[i]].left_top.first - checkConfig->apertureValue / pixEquivalent;

			auto shangXiaPianChaAbs = abs(shangXiaPianCha);
			auto zuoYouPianChaAbs = abs(zuoYouPianCha);

			if (shangXiaPianChaAbs > checkConfig->apertureSimilarity / pixEquivalent || zuoYouPianChaAbs > checkConfig->apertureSimilarity / pixEquivalent)
			{
				isBad = true;

				if (shangXiaPianChaAbs >= zuoYouPianChaAbs)
					errorInfo.emplace_back("孔径 " + QString::number(shangXiaPianCha * pixEquivalent));

				else
					errorInfo.emplace_back("孔径 " + QString::number(zuoYouPianCha * pixEquivalent));
			}
		}

	if (checkConfig->holeCenterDistanceEnable)
		for (int i = 0; i < konJingIndexs.size(); i++)
		{
			auto konCenterY = vecrecogresult[konJingIndexs[i]].left_top.second + (vecrecogresult[konJingIndexs[i]].right_bottom.second - vecrecogresult[konJingIndexs[i]].left_top.second) / 2;
			auto konCenterX = vecrecogresult[konJingIndexs[i]].left_top.first + (vecrecogresult[konJingIndexs[i]].right_bottom.first - vecrecogresult[konJingIndexs[i]].left_top.first) / 2;

			auto konXinJu = ImageTool.CalculateDistance2D(new Point((int)konCenterX, (int)konCenterY), new Point(image.Width / 2, image.Height / 2));
			auto konXinJu = std::sqrt((konCenterX * frame.image.cols / 2) + (konCenterY * frame.image.rows / 2));
			auto pianCha = konXinJu - checkConfig->holeCenterDistanceValue / pixEquivalent;

			if (abs(pianCha) > checkConfig->holeCenterDistanceSimilarity / pixEquivalent)
			{
				isBad = true;

				errorInfo.emplace_back("孔心距 " + QString::number(pianCha * CameraSetting()->xiangShuDangLiang));
			}
		}

	if (checkConfig->edgeDamageEnable)
	{
		for (int i = 0; i < daPoBianIndexs.size(); i++)
		{
			auto score = vecrecogresult[daPoBianIndexs[i]].score;

			if (score > checkConfig->edgeDamageSimilarity)
			{
				isBad = true;
				errorInfo.emplace_back("破边 " + QString::number(score));
			}
		}
	}

	if (checkConfig->brokenEyeEnable)
	{
		for (int i = 0; i < poYanIndexs.size(); i++)
		{
			var area = container.candidates[poYanIndexs[i]].area;
			auto score = vecrecogresult[poYanIndexs[i]].score;
			auto width = abs(vecrecogresult[poYanIndexs[i]].right_bottom.first - vecrecogresult[poYanIndexs[i]].left_top.first);
			auto height = abs(vecrecogresult[poYanIndexs[i]].right_bottom.second - vecrecogresult[poYanIndexs[i]].left_top.second);
			//area > _checkSetting.poYanMianJi&&
			if (score > checkConfig->brokenEyeSimilarity)//&& width * height > CheckSetting()->poYanMianJi
			{
				isBad = true;
				errorInfo.emplace_back("破眼 " + QString::number(score));
			}
		}
	}

	if (checkConfig->crackEnable)
	{
		for (int i = 0; i < lieHenIndexs.size(); i++)
		{
			auto width = abs(vecrecogresult[lieHenIndexs[i]].right_bottom.first - vecrecogresult[lieHenIndexs[i]].left_top.first);
			auto height = abs(vecrecogresult[lieHenIndexs[i]].right_bottom.second - vecrecogresult[lieHenIndexs[i]].left_top.second);

			//var area = container.candidates[lieHenIndexs[i]].area;
			auto score = vecrecogresult[lieHenIndexs[i]].score;
			//area > _checkSetting.lieHenMianJi &&
			if (score > checkConfig->crackSimilarity)//&& width * height > checkConfig->lieHenMianJi
			{
				isBad = true;
				errorInfo.emplace_back("裂痕 " + QString::number(score));

			}
		}
	}

	if (checkConfig->poreEnable)
	{
		for (int i = 0; i < qiKonIndexs.size(); i++)
		{
			auto score = vecrecogresult[qiKonIndexs[i]].score;
			if (score > 30)
			{
				isBad = true;
				errorInfo.emplace_back("气孔 " + QString::number(score));

			}
		}
	}

	if (checkConfig->paintEnable)
	{
		for (int i = 0; i < youQiIndexs.size(); i++)
		{
			auto score = vecrecogresult[youQiIndexs[i]].score;
			if (score > 50)
			{
				isBad = true;
				errorInfo.emplace_back("油漆 " + QString::number(score));

			}
		}
	}

	if (checkConfig->grindStoneEnable)
	{
		for (int i = 0; i < moShiIndexs.size(); i++)
		{
			auto score = vecrecogresult[moShiIndexs[i]].score;
			if (score > 0)
			{
				isBad = true;
				errorInfo.emplace_back("磨石 " + QString::number(score));

			}
		}
	}

	if (checkConfig->blockEyeEnable)
	{
		for (int i = 0; i < duYanIndexs.size(); i++)
		{
			auto score = vecrecogresult[duYanIndexs[i]].score;
			if (score > 10)
			{
				isBad = true;
				errorInfo.emplace_back("堵眼 " + QString::number(score));

			}
		}
	}

	if (checkConfig->materialHeadEnable)
	{
		for (int i = 0; i < liaoTouIndexs.size(); i++)
		{
			auto score = vecrecogresult[liaoTouIndexs[i]].score;
			if (score > 10)
			{
				isBad = true;
				errorInfo.emplace_back("料头 " + QString::number(score));

			}
		}
	}

	// Calculate elapsed time
	t = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
	//LOG () "ProcessMask execution time: " << t*1000 << " seconds";  
	return resultImage.clone();
}

QImage ImageProcessor::cvMatToQImage(const cv::Mat& mat,const QVector<QString>& errorInfo)
{
	QImage result;
	if (mat.type() == CV_8UC1) {
		result= QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_Grayscale8);
	}
	else if (mat.type() == CV_8UC3) {
		result = QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_RGB888).rgbSwapped();
	}
	else if (mat.type() == CV_8UC4) {
		result = QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_RGBA8888);
	}
	else {
		result = QImage();
	}

	ImagePainter::drawTextOnImage(result, errorInfo);


}

ImageProcessor::ImageProcessor(QQueue<MatInfo>& queue, QMutex& mutex, QWaitCondition& condition, int workindex, QObject* parent)
	: QThread(parent), queue(queue), mutex(mutex), condition(condition), workindex(workindex) {
}

void ImageProcessor::run()
{
	while (!QThread::currentThread()->isInterruptionRequested()) {
		MatInfo frame;
		{
			QMutexLocker locker(&mutex);
			if (queue.isEmpty()) {
				condition.wait(&mutex);
				if (QThread::currentThread()->isInterruptionRequested()) {
					break;
				}
			}
			frame = queue.dequeue();
		}

		QVector<QString> errorInfo;
		errorInfo.reserve(20);

		// AI识别处理
		cv::Mat result = processAI(frame, errorInfo);

		// 剔除算法处理
		//result = processElimination(result);

		// 转换为QImage并绘制错误信息
		QImage image = cvMatToQImage(result, errorInfo);

		// 显示到界面
		emit imageReady(image);
		count++;
		LOG() "index:" << workindex << "count" << count;

	}
}

void ImageProcessingModule::BuildModule()
{
	for (int i = 0; i < numConsumers; ++i) {
		static size_t workIndexCount = 0;
		ImageProcessor* processor = new ImageProcessor(queue, mutex, condition, workIndexCount, this);
		workIndexCount++;
		processor->buildModelEngine(modelEnginePath, modelNamePath);
		connect(processor, &ImageProcessor::imageReady, this, &ImageProcessingModule::imageReady, Qt::QueuedConnection);
		processors.push_back(processor);
		processor->start();
	}
}

ImageProcessingModule::ImageProcessingModule(int numConsumers, QObject* parent)
	: QObject(parent), numConsumers(numConsumers) {

}

ImageProcessingModule::~ImageProcessingModule()
{
	// 通知所有线程退出
	for (auto processor : processors) {
		processor->requestInterruption();
	}

	// 唤醒所有等待的线程
	{
		QMutexLocker locker(&mutex);
		condition.wakeAll();
	}

	// 等待所有线程退出
	for (auto processor : processors) {
		if (processor->isRunning()) {
			processor->wait(1000); // 使用超时机制，等待1秒
		}
		delete processor;
	}
}

void ImageProcessingModule::onFrameCaptured(cv::Mat frame, float location, size_t index)
{
	QMutexLocker locker(&mutex);
	MatInfo mat;
	mat.image = frame;
	mat.loaction = location;
	mat.index = index;
	queue.enqueue(mat);
	condition.wakeOne();
}

QColor ImagePainter::ColorToQColor(Color c)
{
	switch (c) {
	case Color::WHITE:   return QColor(255, 255, 255);
	case Color::RED:     return QColor(255, 0, 0);
	case Color::GREEN:   return QColor(0, 255, 0);
	case Color::BLUE:    return QColor(0, 0, 255);
	case Color::YELLOW:  return QColor(255, 255, 0);
	case Color::CYAN:    return QColor(0, 255, 255);
	case Color::MAGENTA: return QColor(255, 0, 255);
	case Color::BLACK:   return QColor(0, 0, 0);
	default:             return QColor(255, 255, 255);
	}
}

void ImagePainter::drawTextOnImage(QImage& image, const QVector<QString>& texts, const QVector<Color>& colorList, double proportion)
{
	// 确保图像非空
	if (image.isNull() || texts.empty() || proportion <= 0.0 || proportion > 1.0) {
		return;
	}

	// 创建 QPainter
	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	// 计算字体大小和初始位置
	int imageHeight = image.height();
	int textAreaHeight = static_cast<int>(imageHeight * proportion); // 根据比例计算文字区域高度
	int yOffset = 10; // 初始Y偏移量

	// 动态调整字体大小
	QFont font("Arial");
	int fontSize = 20; // 初始字体大小
	font.setPixelSize(fontSize);
	painter.setFont(font);

	// 计算动态字体大小
	for (const auto& text : texts) {
		QRect textRect(0, 0, image.width(), textAreaHeight);
		QFontMetrics metrics(font);
		if (metrics.height() * texts.size() > textAreaHeight) {
			fontSize = static_cast<int>(fontSize * 0.9); // 缩小字体
			font.setPixelSize(fontSize);
			painter.setFont(font);
		}
	}

	// 绘制文字
	for (size_t i = 0; i < texts.size(); ++i) {
		// 确定颜色
		Color textColor = Color::WHITE; // 默认白色
		if (!colorList.empty()) {
			if (i < colorList.size()) {
				textColor = colorList[i];
			}
			else {
				textColor = colorList.back(); // 使用最后一个颜色
			}
		}

		// 设置颜色
		painter.setPen(ColorToQColor(textColor));

		// 绘制文字
		QString qText = texts[i];
		painter.drawText(10, yOffset + fontSize, qText); // 左上角偏移量为 (10, yOffset)
		yOffset += fontSize + 5; // 行间距
	}

	painter.end();
}

