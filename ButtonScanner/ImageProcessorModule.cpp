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

	for (int i = 0; i < vecRecogResult.size(); i++)
	{
		switch (vecRecogResult[i].classId)
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

	std::vector<rw::ime::ProcessRectanglesResult> body;
	std::vector<rw::ime::ProcessRectanglesResult> hole;

	//拆分body和hole
	for (const auto & item:vecRecogResult) {
		if (item.classId==0) {
			body.emplace_back(item);
		}
		else if (item.classId==1) {
            hole.emplace_back(item);
		}
		
	}

	if (checkConfig->outsideDiameterEnable)
		ImagePainter::drawCirclesOnImage(resultImage, body);
		if (waiJingIndexs.size() == 0)
		{
			isBad = true;
			errorInfo.emplace_back("没找到外径");
		}
		else
		{
			auto shangXiaPianCha = vecRecogResult[waiJingIndexs[0]].right_bottom.second - vecRecogResult[waiJingIndexs[0]].left_top.second - checkConfig->outsideDiameterValue / pixEquivalent;
			auto zuoYouPianCha = vecRecogResult[waiJingIndexs[0]].right_bottom.first - vecRecogResult[waiJingIndexs[0]].left_top.first - checkConfig->outsideDiameterValue / pixEquivalent;

			auto shangXiaPianChaAbs = abs(shangXiaPianCha);
			auto zuoYouPianChaAbs = abs(zuoYouPianCha);

			if (shangXiaPianChaAbs > checkConfig->outsideDiameterDeviation / pixEquivalent || zuoYouPianChaAbs > checkConfig->outsideDiameterDeviation / pixEquivalent)
			{
				isBad = true;

				if (shangXiaPianChaAbs >= zuoYouPianChaAbs)
					errorInfo.emplace_back("外径 "+QString::number(shangXiaPianCha * pixEquivalent));
				else
					errorInfo.emplace_back("外径 " + QString::number(zuoYouPianCha * pixEquivalent));
			}
		}

	if (checkConfig->holesCountEnable)
		ImagePainter::drawCirclesOnImage(resultImage, hole);
		if (konJingIndexs.size() != checkConfig->holesCountValue)
		{
			isBad = true;
			errorInfo.emplace_back("只找到" + QString::number(konJingIndexs.size()) + "个孔");
		}

	if (checkConfig->apertureEnable)
		for (int i = 0; i < konJingIndexs.size(); i++)
		{
			auto shangXiaPianCha = vecRecogResult[konJingIndexs[i]].right_bottom.second - vecRecogResult[konJingIndexs[i]].left_top.second - checkConfig->apertureValue / pixEquivalent;
			auto zuoYouPianCha = vecRecogResult[konJingIndexs[i]].right_bottom.first - vecRecogResult[konJingIndexs[i]].left_top.first - checkConfig->apertureValue / pixEquivalent;

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
			auto konCenterY = vecRecogResult[konJingIndexs[i]].left_top.second + (vecRecogResult[konJingIndexs[i]].right_bottom.second - vecRecogResult[konJingIndexs[i]].left_top.second) / 2;
			auto konCenterX = vecRecogResult[konJingIndexs[i]].left_top.first + (vecRecogResult[konJingIndexs[i]].right_bottom.first - vecRecogResult[konJingIndexs[i]].left_top.first) / 2;

			auto konXinJu = std::sqrt((konCenterX * frame.image.cols / 2) + (konCenterY * frame.image.rows / 2));
			auto pianCha = konXinJu - checkConfig->holeCenterDistanceValue / pixEquivalent;

			if (abs(pianCha) > checkConfig->holeCenterDistanceSimilarity / pixEquivalent)
			{
				isBad = true;

				errorInfo.emplace_back("孔心距 " + QString::number(pianCha * pixEquivalent));
			}
		}

	if (checkConfig->edgeDamageEnable)
	{
		for (int i = 0; i < daPoBianIndexs.size(); i++)
		{
			auto score = vecRecogResult[daPoBianIndexs[i]].score;

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
			//auto area = vecRecogResult[poYanIndexs[i]].area;
			auto score = vecRecogResult[poYanIndexs[i]].score;
			auto width = abs(vecRecogResult[poYanIndexs[i]].right_bottom.first - vecRecogResult[poYanIndexs[i]].left_top.first);
			auto height = abs(vecRecogResult[poYanIndexs[i]].right_bottom.second - vecRecogResult[poYanIndexs[i]].left_top.second);
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
			auto width = abs(vecRecogResult[lieHenIndexs[i]].right_bottom.first - vecRecogResult[lieHenIndexs[i]].left_top.first);
			auto height = abs(vecRecogResult[lieHenIndexs[i]].right_bottom.second - vecRecogResult[lieHenIndexs[i]].left_top.second);

			//var area = container.candidates[lieHenIndexs[i]].area;
			auto score = vecRecogResult[lieHenIndexs[i]].score;
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
			auto score = vecRecogResult[qiKonIndexs[i]].score;
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
			auto score = vecRecogResult[youQiIndexs[i]].score;
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
			auto score = vecRecogResult[moShiIndexs[i]].score;
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
			auto score = vecRecogResult[duYanIndexs[i]].score;
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
			auto score = vecRecogResult[liaoTouIndexs[i]].score;
			if (score > 10)
			{
				isBad = true;
				errorInfo.emplace_back("料头 " + QString::number(score));

			}
		}
	}

	LOG()errorInfo.size();

    emit processResult(!isBad, frame.loaction);

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

	return result;
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
        connect(processor, &ImageProcessor::processResult, this, &ImageProcessingModule::onProcessResult, Qt::QueuedConnection);
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

void ImageProcessingModule::onProcessResult(bool isOk, float location)
{
    emit processResult(isOk, location);
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

void ImagePainter::drawCirclesOnImage(cv::Mat& image, const std::vector<rw::ime::ProcessRectanglesResult>& rectangles)
{
	for (const auto& rect : rectangles) {
		// 计算矩形中心点
		int centerX = (rect.left_top.first + rect.right_bottom.first) / 2;
		int centerY = (rect.left_top.second + rect.right_bottom.second) / 2;

		// 计算矩形的宽度和高度
		int width = rect.right_bottom.first - rect.left_top.first;
		int height = rect.right_bottom.second - rect.left_top.second;

		// 计算圆的半径（取宽度和高度的较小值的一半）
		int radius = std::min(width, height) / 2;

		// 使用 mask_r, mask_g, mask_b 作为圆的颜色
		cv::Scalar color(0,165,255);

		// 在图像上绘制圆
		cv::circle(image, cv::Point(centerX, centerY), radius, color,5); // 2 表示线宽
	}
}

