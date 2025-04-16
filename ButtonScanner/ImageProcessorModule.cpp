#include"stdafx.h"
#include "GlobalStruct.h"
#include"ImageProcessorModule.h"
#include"StatisticalInfoComputingThread.h"
#include"imeoo_ModelEngineOO.h"
#include <QtConcurrent> 

void ImageProcessor::buildModelEngine(const QString& enginePath, const QString& namePath)
{
	_modelEnginePtr = std::make_unique<rw::imeot::ModelEngineOT>(enginePath.toStdString(), namePath.toStdString());
}

void ImageProcessor::buildModelEngineOnnx(const QString& enginePath, const QString& namePath)
{
	_modelEnginePtrOnnx = std::make_unique<rw::imeoo::ModelEngineOO>(enginePath.toStdString(), namePath.toStdString());
}

bool ImageProcessor::isInAred(int x)
{
	auto& globalStruct = GlobalStructData::getInstance();
	if (imageProcessingModuleIndex == 1)
	{
		auto& lineLeft = globalStruct.dlgProduceLineSetConfig.limit1;
		auto lineRight = lineLeft + (globalStruct.dlgProductSetConfig.outsideDiameterValue / globalStruct.dlgProduceLineSetConfig.pixelEquivalent1);
		if (lineLeft < x && x < lineRight)
		{
			return true;
		}
	}
	else if (imageProcessingModuleIndex == 2)
	{
		auto& lineRight = globalStruct.dlgProduceLineSetConfig.limit2;
		auto lineLeft = lineRight - (globalStruct.dlgProductSetConfig.outsideDiameterValue / globalStruct.dlgProduceLineSetConfig.pixelEquivalent2);
		if (lineLeft < x && x < lineRight)
		{
			return true;
		}
	}
	else if (imageProcessingModuleIndex == 3)
	{
		auto& lineLeft = globalStruct.dlgProduceLineSetConfig.limit3;
		auto lineRight = lineLeft + (globalStruct.dlgProductSetConfig.outsideDiameterValue / globalStruct.dlgProduceLineSetConfig.pixelEquivalent3);
		if (lineLeft < x && x < lineRight)
		{
			return true;
		}
	}
	else if (imageProcessingModuleIndex == 4)
	{
		auto& lineRight = globalStruct.dlgProduceLineSetConfig.limit4;
		auto lineLeft = lineRight - (globalStruct.dlgProductSetConfig.outsideDiameterValue / globalStruct.dlgProduceLineSetConfig.pixelEquivalent4);
		if (lineLeft < x && x < lineRight)
		{
			return true;
		}
	}
	return false;
}

std::vector<rw::imeot::ProcessRectanglesResultOT> ImageProcessor::getDefectInBody(rw::imeot::ProcessRectanglesResultOT body, const std::vector<rw::imeot::ProcessRectanglesResultOT>& vecRecogResult)
{
	static int i = 0;
	std::vector<rw::imeot::ProcessRectanglesResultOT> result;
	auto& globalStruct = GlobalStructData::getInstance();

	auto leleltMin = body.left_top.first;
	auto leleltMax = body.right_bottom.first;
	auto verticalMin = body.left_top.second;
	auto verticalMax = body.right_bottom.second;

	
	for (const auto & item: vecRecogResult)
	{
		if (leleltMin<item.center_x&& item.center_x<leleltMax)
		{
			if (verticalMin<item.center_y&&item.center_y<verticalMax)
			{
				result.emplace_back(item);
			}
		}
	}
	return result;
}

cv::Mat ImageProcessor::processAI(MatInfo& frame, QVector<QString>& errorInfo, std::vector<rw::imeot::ProcessRectanglesResultOT>& vecRecogResult, std::vector<rw::imeot::ProcessRectanglesResultOT> & vecRecogResultTarget)
{
	auto& globalStruct = GlobalStructData::getInstance();

	cv::Mat resultImage1;
	std::vector<rw::imeoo::ProcessRectanglesResultOO > vecRecogResultOnnx;
	// 使用 QtConcurrent::run 将 _modelEnginePtrOnnx->ProcessMask 放到后台线程中执行
	QFuture<void> onnxFuture = QtConcurrent::run([&]() {
		_modelEnginePtrOnnx->ProcessMask(frame.image, resultImage1, vecRecogResultOnnx);
		});

	cv::Mat resultImage;
	cv::Mat maskImage = cv::Mat::zeros(frame.image.size(), CV_8UC1);

	_modelEnginePtr->ProcessMask(frame.image, resultImage, vecRecogResult);

	onnxFuture.waitForFinished();

	if (globalStruct.isOpenRemoveFunc || (globalStruct.isDebugMode)) {
		bool hasBody;
		auto body = getBody(vecRecogResult, hasBody);
		if (!hasBody)
		{
			if (globalStruct.isOpenRemoveFunc) {

				globalStruct.statisticalInfo.wasteCount++;


				if (imageProcessingModuleIndex == 2 || imageProcessingModuleIndex == 4) {
					globalStruct.statisticalInfo.produceCount++;
				}


				float absLocation = frame.location;
				if (absLocation < 0) {
					absLocation = -absLocation; // 将负值转换为正值
				}

				switch (imageProcessingModuleIndex)
				{
				case 1:
					globalStruct.productPriorityQueue1.push(absLocation);
					break;
				case 2:
					globalStruct.productPriorityQueue2.push(absLocation);
					break;
				case 3:
					globalStruct.productPriorityQueue3.push(absLocation);
					break;
				case 4:
					globalStruct.productPriorityQueue4.push(absLocation);
					break;
				default:
					break;
				}

			}
			if (globalStruct.isTakePictures) {
				globalStruct.imageSaveEngine->pushImage(cvMatToQImage(frame.image), "NG", "Button");
				globalStruct.imageSaveEngine->pushImage(cvMatToQImage(frame.image), "OK", "Button");
			}

		}
		else
		{
			auto defect = getDefectInBody(body, vecRecogResult);
			eliminationLogic(frame, frame.image,errorInfo,defect, vecRecogResultTarget);
		}
	}
	//如果新物料学习窗口在步骤1（学习坏的）、2（学习好的），就调用dlgAiLearn->onFrameCaptured
	if (globalStruct.mainWindow->dlgAiLearn->step > 0 && globalStruct.mainWindow->dlgAiLearn->step < 3) {
		globalStruct.mainWindow->dlgAiLearn->onFrameCaptured(frame.image, frame.index);
	}

	return frame.image.clone();
}

rw::imeot::ProcessRectanglesResultOT ImageProcessor::getBody(std::vector<rw::imeot::ProcessRectanglesResultOT>& processRectanglesResult, bool& hasBody)
{
	hasBody = false;
	rw::imeot::ProcessRectanglesResultOT result;
	for (auto& i : processRectanglesResult)
	{
		if (i.classID == 0)
		{
			auto isInArea=isInAred(i.center_x);
			if (isInArea)
			{
				result = i;
				hasBody = true;
				break;
			}
		}
	}
	LOG() "result.x" << result.center_x << "result.y" << result.center_y;
	LOG() "result.classID" << result.classID;
	return result;
}


void ImageProcessor::eliminationLogic(MatInfo& frame, cv::Mat& resultImage, QVector<QString>& errorInfo, std::vector<rw::imeot::ProcessRectanglesResultOT>& processRectanglesResult, std::vector<rw::imeot::ProcessRectanglesResultOT> & vecRecogResultTarget)
{
	auto saveIamge = resultImage.clone();
	auto& globalStruct = GlobalStructData::getInstance();

	auto& systemConfig = globalStruct.dlgProduceLineSetConfig;
	auto& checkConfig = globalStruct.dlgProductSetConfig;

	double& pixEquivalent = systemConfig.pixelEquivalent1;
	switch (frame.index)
	{
	case 2:
		pixEquivalent = systemConfig.pixelEquivalent2;
		break;
	case 3:
		pixEquivalent = systemConfig.pixelEquivalent3;
		break;
	case 4:
		pixEquivalent = systemConfig.pixelEquivalent4;
		break;
	default:
		break;
	}

	auto isBad = false;

	cv::Mat resultMat;
	cv::Mat maskmat;

	std::vector<int> waiJingIndexs = std::vector<int>();
	size_t holesCount = 0;
	std::vector<int> konJingIndexs = std::vector<int>();
	std::vector<int> daPoBianIndexs = std::vector<int>();
	std::vector<int> qiKonIndexs = std::vector<int>();
	std::vector<int> duYanIndexs = std::vector<int>();
	std::vector<int> moShiIndexs = std::vector<int>();
	std::vector<int> liaoTouIndexs = std::vector<int>();
	std::vector<int> youQiIndexs = std::vector<int>();
	std::vector<int> lieHenIndexs = std::vector<int>();
	std::vector<int> poYanIndexs = std::vector<int>();

	for (int i = 0; i < processRectanglesResult.size(); i++)
	{
		switch (processRectanglesResult[i].classID)
		{
		case 0: waiJingIndexs.push_back(i); continue;
		case 1: holesCount++; konJingIndexs.push_back(i); continue;
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

	// 检查外径是否被识别成小孔
	if (!konJingIndexs.empty()) {
		// 计算小孔的平均高度和宽度
		double totalHeight = 0.0, totalWidth = 0.0;
		for (int index : konJingIndexs) {
			const auto& rect = processRectanglesResult[index];
			int height = rect.right_bottom.second - rect.left_top.second;
			int width = rect.right_bottom.first - rect.left_top.first;
			totalHeight += height;
			totalWidth += width;
		}
		double avgHeight = totalHeight / konJingIndexs.size();
		double avgWidth = totalWidth / konJingIndexs.size();

		// 允许的偏差比例（可以根据实际情况调整）
		const double deviationRatio = 0.8;

		// 剔除偏离平均值过大的矩形
		for (int i = 0; i < konJingIndexs.size(); ++i) {
			int index = konJingIndexs[i];
			const auto& rect = processRectanglesResult[index];
			int height = rect.right_bottom.second - rect.left_top.second;
			int width = rect.right_bottom.first - rect.left_top.first;

			// 判断是否偏离平均值
			if (std::abs(height - avgHeight) > avgHeight * deviationRatio ||
				std::abs(width - avgWidth) > avgWidth * deviationRatio) {
				// 偏离过大，剔除
				konJingIndexs.erase(konJingIndexs.begin() + i);
				holesCount--;
				--i; // 调整索引以避免跳过下一个元素
			}
		}
	}

	std::vector<rw::imeot::ProcessRectanglesResultOT> body;
	std::vector<rw::imeot::ProcessRectanglesResultOT> hole;

	//拾取外径和孔径
	for (int i = 0;i < waiJingIndexs.size();i++)
	{
		body.emplace_back(processRectanglesResult[waiJingIndexs[i]]);
	}
	for (int i = 0;i < konJingIndexs.size();i++)
	{
		hole.emplace_back(processRectanglesResult[konJingIndexs[i]]);
	}

	//检查外径
	if (checkConfig.outsideDiameterEnable)
	{
		ImagePainter::drawCirclesOnImage(resultImage, body);
		if (waiJingIndexs.size() == 0)
		{
			isBad = true;
			errorInfo.emplace_back("没找到外径");
		}
		else
		{
			auto shangXiaPianCha = processRectanglesResult[waiJingIndexs[0]].right_bottom.second - processRectanglesResult[waiJingIndexs[0]].left_top.second - checkConfig.outsideDiameterValue / pixEquivalent;
			auto zuoYouPianCha = processRectanglesResult[waiJingIndexs[0]].right_bottom.first - processRectanglesResult[waiJingIndexs[0]].left_top.first - checkConfig.outsideDiameterValue / pixEquivalent;

			auto shangXiaPianChaAbs = abs(shangXiaPianCha);
			auto zuoYouPianChaAbs = abs(zuoYouPianCha);

			if (shangXiaPianChaAbs > checkConfig.outsideDiameterDeviation / pixEquivalent || zuoYouPianChaAbs > checkConfig.outsideDiameterDeviation / pixEquivalent)
			{
				isBad = true;

				if (shangXiaPianChaAbs >= zuoYouPianChaAbs)
				{
					errorInfo.emplace_back("外径 " + QString::number(shangXiaPianCha * pixEquivalent));
				}
				else
				{
					errorInfo.emplace_back("外径 " + QString::number(zuoYouPianCha * pixEquivalent));
				}
				
			}
		}
	}

	//检查孔数
	if (checkConfig.holesCountEnable)
	{
		ImagePainter::drawCirclesOnImage(resultImage, hole);
		// 获取当前时间
		auto now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count() % 60;
		auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count() % 60;

		// 格式化时间
		std::ostringstream timeStream;
		timeStream << std::setfill('0') << std::setw(2) << minutes << "_"
			<< std::setfill('0') << std::setw(2) << seconds << "_"
			<< std::setfill('0') << std::setw(3) << millis;

		if (holesCount != checkConfig.holesCountValue)
		{
			isBad = true;
			errorInfo.emplace_back("只找到" + QString::number(holesCount) + "个孔");
			

		}
	}

	//检查大破边
	if (checkConfig.edgeDamageEnable)
	{
		for (int i = 0; i < daPoBianIndexs.size(); i++)
		{
			auto score = processRectanglesResult[daPoBianIndexs[i]].score;

			if (score >= (checkConfig.edgeDamageSimilarity) / 100)
			{
				isBad = true;
				errorInfo.emplace_back("破边 " + QString::number(score));
				for (int i = 0;i < daPoBianIndexs.size();i++)
				{
					vecRecogResultTarget.emplace_back(processRectanglesResult[daPoBianIndexs[i]]);
				}
			}
		}
	}
	//检查气孔
	if (checkConfig.poreEnable)
	{
		for (int i = 0; i < qiKonIndexs.size(); i++)
		{
			auto score = processRectanglesResult[qiKonIndexs[i]].score;
			if (score >= 0.3)
			{
				isBad = true;
				errorInfo.emplace_back("气孔 " + QString::number(score));
				for (int i = 0;i < qiKonIndexs.size();i++)
				{
					vecRecogResultTarget.emplace_back(processRectanglesResult[qiKonIndexs[i]]);
				}
			}
		}
	}

	//检查堵眼
	if (checkConfig.blockEyeEnable)
	{
		for (int i = 0; i < duYanIndexs.size(); i++)
		{
			auto score = processRectanglesResult[duYanIndexs[i]].score;
			if (score >= 0.1)
			{
				isBad = true;
				errorInfo.emplace_back("堵眼 " + QString::number(score));
				for (int i = 0;i < duYanIndexs.size();i++)
				{
					vecRecogResultTarget.emplace_back(processRectanglesResult[duYanIndexs[i]]);
				}
			}
		}
	}

	//检查磨石
	if (checkConfig.grindStoneEnable)
	{
		for (int i = 0; i < moShiIndexs.size(); i++)
		{
			auto score = processRectanglesResult[moShiIndexs[i]].score;
			if (score >= 0.1)
			{
				isBad = true;
				errorInfo.emplace_back("磨石 " + QString::number(score));
				for (int i = 0;i < moShiIndexs.size();i++)
				{
					vecRecogResultTarget.emplace_back(processRectanglesResult[moShiIndexs[i]]);
				}
			}
		}
	}

	//检查料头
	if (checkConfig.materialHeadEnable)
	{
		for (int i = 0; i < liaoTouIndexs.size(); i++)
		{
			auto score = processRectanglesResult[liaoTouIndexs[i]].score;
			if (score >= 0.1)
			{
				isBad = true;
				errorInfo.emplace_back("料头 " + QString::number(score));
				for (int i = 0;i < liaoTouIndexs.size();i++)
				{
					vecRecogResultTarget.emplace_back(processRectanglesResult[liaoTouIndexs[i]]);
				}
			}
		}
	}

	//检查脏污
	if (checkConfig.paintEnable)
	{
		for (int i = 0; i < youQiIndexs.size(); i++)
		{
			auto score = processRectanglesResult[youQiIndexs[i]].score;
			if (score >= 0.5)
			{
				isBad = true;
				errorInfo.emplace_back("油漆 " + QString::number(score));
				for (int i = 0;i < youQiIndexs.size();i++)
				{
					vecRecogResultTarget.emplace_back(processRectanglesResult[youQiIndexs[i]]);
				}
			}
		}
	}

	//检查裂痕
	if (checkConfig.crackEnable)
	{
		for (int i = 0; i < lieHenIndexs.size(); i++)
		{
			auto width = abs(processRectanglesResult[lieHenIndexs[i]].right_bottom.first - processRectanglesResult[lieHenIndexs[i]].left_top.first);
			auto height = abs(processRectanglesResult[lieHenIndexs[i]].right_bottom.second - processRectanglesResult[lieHenIndexs[i]].left_top.second);

			auto score = processRectanglesResult[lieHenIndexs[i]].score;
			if (score >= checkConfig.crackSimilarity / 100)
			{
				isBad = true;
				errorInfo.emplace_back("裂痕 " + QString::number(score));
				for (int i = 0;i < lieHenIndexs.size();i++)
				{
					vecRecogResultTarget.emplace_back(processRectanglesResult[lieHenIndexs[i]]);
				}
			}
		}
	}

	////检查小气孔

	//if (checkConfig.brokenEyeEnable)
	//{
	//	for (int i = 0; i < poYanIndexs.size(); i++)
	//	{
	//		auto score = processRectanglesResult[poYanIndexs[i]].score;
	//		auto width = abs(processRectanglesResult[poYanIndexs[i]].right_bottom.first - processRectanglesResult[poYanIndexs[i]].left_top.first);
	//		auto height = abs(processRectanglesResult[poYanIndexs[i]].right_bottom.second - processRectanglesResult[poYanIndexs[i]].left_top.second);
	//		if (score >= checkConfig.brokenEyeSimilarity)
	//		{
	//			isBad = true;
	//			errorInfo.emplace_back("破眼 " + QString::number(score));
	//			for (int i = 0;i < poYanIndexs.size();i++)
	//			{
	//				vecRecogResultTarget.emplace_back(processRectanglesResult[poYanIndexs[i]]);
	//			}
	//		}
	//	}
	//}

	////检查小破边
	//if (checkConfig.apertureEnable)
	//{
	//	for (int i = 0; i < konJingIndexs.size(); i++)
	//	{
	//		auto shangXiaPianCha = processRectanglesResult[konJingIndexs[i]].right_bottom.second - processRectanglesResult[konJingIndexs[i]].left_top.second - checkConfig.apertureValue / pixEquivalent;
	//		auto zuoYouPianCha = processRectanglesResult[konJingIndexs[i]].right_bottom.first - processRectanglesResult[konJingIndexs[i]].left_top.first - checkConfig.apertureValue / pixEquivalent;

	//		auto shangXiaPianChaAbs = abs(shangXiaPianCha);
	//		auto zuoYouPianChaAbs = abs(zuoYouPianCha);

	//		if (shangXiaPianChaAbs > checkConfig.apertureSimilarity / pixEquivalent || zuoYouPianChaAbs > checkConfig.apertureSimilarity / pixEquivalent)
	//		{
	//			isBad = true;

	//			if (shangXiaPianChaAbs >= zuoYouPianChaAbs)
	//			{
	//				errorInfo.emplace_back("孔径 " + QString::number(shangXiaPianCha * pixEquivalent));
	//				for (int i = 0;i < poYanIndexs.size();i++)
	//				{
	//					vecRecogResultTarget.emplace_back(processRectanglesResult[poYanIndexs[i]]);
	//				}
	//			}
	//			else
	//			{
	//				errorInfo.emplace_back("孔径 " + QString::number(zuoYouPianCha * pixEquivalent));
	//				for (int i = 0;i < poYanIndexs.size();i++)
	//				{
	//					vecRecogResultTarget.emplace_back(processRectanglesResult[poYanIndexs[i]]);
	//				}
	//			}

	//		}
	//	}
	//}

	//检查孔心距
	if (checkConfig.holeCenterDistanceEnable)
	{
		for (int i = 0; i < konJingIndexs.size(); i++)
		{
			auto konCenterY = processRectanglesResult[konJingIndexs[i]].left_top.second + (processRectanglesResult[konJingIndexs[i]].right_bottom.second - processRectanglesResult[konJingIndexs[i]].left_top.second) / 2;
			auto konCenterX = processRectanglesResult[konJingIndexs[i]].left_top.first + (processRectanglesResult[konJingIndexs[i]].right_bottom.first - processRectanglesResult[konJingIndexs[i]].left_top.first) / 2;

			auto konXinJu = std::sqrt((konCenterX * frame.image.cols / 2) + (konCenterY * frame.image.rows / 2));
			auto pianCha = konXinJu - checkConfig.holeCenterDistanceValue / pixEquivalent;

			if (abs(pianCha) > checkConfig.holeCenterDistanceSimilarity / pixEquivalent)
			{
				isBad = true;

				errorInfo.emplace_back("孔心距 " + QString::number(pianCha * pixEquivalent));
			}
		}
	}

	if (globalStruct.isOpenRemoveFunc) {
		if (isBad) {
			globalStruct.statisticalInfo.wasteCount++;
		}

		if (imageProcessingModuleIndex == 2 || imageProcessingModuleIndex == 4) {
			globalStruct.statisticalInfo.produceCount++;
		}

		if (isBad) {
			float absLocation = frame.location;
			if (absLocation < 0) {
				absLocation = -absLocation; // 将负值转换为正值
			}

			switch (imageProcessingModuleIndex)
			{
			case 1:
				globalStruct.productPriorityQueue1.push(absLocation);
				break;
			case 2:
				globalStruct.productPriorityQueue2.push(absLocation);
				break;
			case 3:
				globalStruct.productPriorityQueue3.push(absLocation);
				break;
			case 4:
				globalStruct.productPriorityQueue4.push(absLocation);
				break;
			default:
				break;
			}
		}

	}

	if (globalStruct.isTakePictures) {
		if (isBad) {
			globalStruct.imageSaveEngine->pushImage(cvMatToQImage(saveIamge), "NG", "Button");
		}
		else {
			globalStruct.imageSaveEngine->pushImage(cvMatToQImage(saveIamge), "OK", "Button");
		}
	}
}

QImage ImageProcessor::cvMatToQImage(const cv::Mat& mat)
{
	QImage result;
	if (mat.type() == CV_8UC1) {
		result = QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_Grayscale8);
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

	return result;
}

void ImageProcessor::drawErrorLocate(QImage& image, std::vector<rw::imeot::ProcessRectanglesResultOT>& vecRecogResult, const QColor& drawColor)
{
	auto& globalStructLineSetConfig = GlobalStructData::getInstance().dlgProduceLineSetConfig;
	double pixEquivalent;
	switch (imageProcessingModuleIndex)
	{
	case 1:
		pixEquivalent = globalStructLineSetConfig.pixelEquivalent1;
		break;
	case 2:
		pixEquivalent = globalStructLineSetConfig.pixelEquivalent2;
		break;
	case 3:
		pixEquivalent = globalStructLineSetConfig.pixelEquivalent3;
		break;
	case 4:
		pixEquivalent = globalStructLineSetConfig.pixelEquivalent4;
		break;
	}

	auto& checkConfig = GlobalStructData::getInstance().dlgProductSetConfig;
	if (image.isNull()) {
		return;
	}
	for (const auto& item : vecRecogResult) {
		if (item.classID == 0 || item.classID == 1) {
			continue;
		}
		if (!checkConfig.edgeDamageEnable && item.classID == 2)
		{
			continue;
		}
		if (!checkConfig.poreEnable && item.classID == 3)
		{
			continue;
		}
		if (!checkConfig.blockEyeEnable && item.classID == 4)
		{
			continue;
		}
		if (!checkConfig.grindStoneEnable && item.classID == 5)
		{
			continue;
		}
		if (!checkConfig.materialHeadEnable && item.classID == 6)
		{
			continue;
		}
		if (!checkConfig.paintEnable && item.classID == 7)
		{
			continue;
		}
		if (!checkConfig.crackEnable && item.classID == 8)
		{
			continue;
		}
		if (!checkConfig.brokenEyeEnable && item.classID == 9)
		{
			continue;
		}

		auto leftTop = item.left_top;
		auto rightBottom = item.right_bottom;

		// 绘制矩形框
		QPainter painter(&image);
		painter.setPen(QPen(drawColor, 5)); // 使用传入的颜色
		painter.drawRect(QRect(leftTop.first, leftTop.second, rightBottom.first - leftTop.first, rightBottom.second - leftTop.second));

		// 设置字体大小
		QFont font = painter.font();
		font.setPixelSize(50); // 将字体大小设置为 50 像素（可以根据需要调整）
		painter.setFont(font);

		// 绘制文字
		QString text;

		switch (item.classID)
		{
		case 2:
			text = "破边";
			break;
		case 3:
			text = "气孔";
			break;
		case 4:
			text = "堵眼";
			break;
		case 5:
			text = "磨石";
			break;
		case 6:
			text = "料头";
			break;
		case 7:
			text = "脏污";
			break;
		case 8:
			text = "裂痕";
			break;
		case 9:
			text = "破眼";
			break;
		case 10:
			text = "小气孔";
			break;
		case 11:
			text = "毛发";
			break;
		case 12:
			text = "小破边";
			break;
		case 13:
			text = "白边";
			break;
		default:
			text = QString::number(item.classID);
			break;
		}
		int score = item.score * 100;
		auto area = std::round(item.height * item.width * pixEquivalent * 10) / 10.0; // 保留一位小数
		text = text + QString::number(score) + " " + QString::number(area);

		// 设置文字颜色
		painter.setPen(drawColor); // 使用传入的颜色
		painter.drawText(leftTop.first, leftTop.second - 5, text);
	}
}

void ImageProcessor::drawLine(QImage& image)
{
	auto& index = imageProcessingModuleIndex;
	auto& dlgProduceLineSetConfig = GlobalStructData::getInstance().dlgProduceLineSetConfig;
	auto& checkConfig = GlobalStructData::getInstance().dlgProductSetConfig;
	if (index == 1)
	{
		drawLine_locate(image, dlgProduceLineSetConfig.limit1);
		drawLine_locate(image, dlgProduceLineSetConfig.limit1 + (checkConfig.outsideDiameterValue / dlgProduceLineSetConfig.pixelEquivalent1));
	}
	else if (index == 2)
	{
		drawLine_locate(image, dlgProduceLineSetConfig.limit2);
		drawLine_locate(image, dlgProduceLineSetConfig.limit2 - (checkConfig.outsideDiameterValue / dlgProduceLineSetConfig.pixelEquivalent2));
	}
	else if (index == 3)
	{
		drawLine_locate(image, dlgProduceLineSetConfig.limit3);
		drawLine_locate(image, dlgProduceLineSetConfig.limit3 + (checkConfig.outsideDiameterValue / dlgProduceLineSetConfig.pixelEquivalent3));
	}
	else if (index == 4)
	{
		drawLine_locate(image, dlgProduceLineSetConfig.limit4);
		drawLine_locate(image, dlgProduceLineSetConfig.limit4 - (checkConfig.outsideDiameterValue / dlgProduceLineSetConfig.pixelEquivalent4));
	}
}

void ImageProcessor::drawLine_locate(QImage& image, size_t locate)
{
	if (image.isNull() || locate >= static_cast<size_t>(image.width())) {
		return; // 如果图像无效或 locate 超出图像宽度，直接返回
	}

	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing); // 开启抗锯齿
	painter.setPen(QPen(Qt::red, 2)); // 设置画笔颜色为红色，线宽为2像素

	// 绘制竖线，从图像顶部到底部
	painter.drawLine(QPoint(locate, 0), QPoint(locate, image.height()));

	painter.end(); // 结束绘制
}

ImageProcessor::ImageProcessor(QQueue<MatInfo>& queue, QMutex& mutex, QWaitCondition& condition, int workIndex, QObject* parent)
	: QThread(parent), _queue(queue), _mutex(mutex), _condition(condition), _workIndex(workIndex) {
}

void ImageProcessor::run()
{
	while (!QThread::currentThread()->isInterruptionRequested()) {
		MatInfo frame;
		{
			QMutexLocker locker(&_mutex);
			if (_queue.isEmpty()) {
				_condition.wait(&_mutex);
				if (QThread::currentThread()->isInterruptionRequested()) {
					break;
				}
			}
			if (!_queue.isEmpty()) {
				frame = _queue.dequeue();
			}
			else {
				continue; // 如果队列仍为空，跳过本次循环
			}
		}

		// 检查 frame 是否有效
		if (frame.image.empty()) {
			continue; // 跳过空帧
		}

		QVector<QString> processInfo;
		processInfo.reserve(20);

		std::vector<rw::imeot::ProcessRectanglesResultOT> vecRecogResultBad;
		std::vector<rw::imeot::ProcessRectanglesResultOT> vecRecogResultTarget;

		// 开始计时
		auto startTime = std::chrono::high_resolution_clock::now();

		//预留处理时间的位子
		processInfo.emplace_back();

		// 调用 processAI 函数
		cv::Mat result = processAI(frame, processInfo, vecRecogResultBad, vecRecogResultTarget);

		// 结束计时
		auto endTime = std::chrono::high_resolution_clock::now();

		// 计算耗时
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

		processInfo[0] = QString("处理时间: %1 ms").arg(duration);

		auto  image = cvMatToQImage(result);

		// 绘制错误信息
		ImagePainter::drawTextOnImage(image, processInfo, { ImagePainter::Color::Green,ImagePainter::Color::Red }, 0.07);

		// 绘制错误定位全局错误定位
		drawErrorLocate(image, vecRecogResultBad, Qt::green);

		
		// 绘制错误定位目标定位
		drawErrorLocate(image, vecRecogResultTarget, Qt::red); 


		drawLine(image);

		if (GlobalStructData::getInstance().isTakePictures) {
			GlobalStructData::getInstance().imageSaveEngine->pushImage(image, "Mark", "Button");
		}

		QPixmap pixmap = QPixmap::fromImage(image);
		// 显示到界面
		emit imageReady(pixmap);
	}
}

void ImageProcessingModule::BuildModule()
{
	for (int i = 0; i < _numConsumers; ++i) {
		static size_t workIndexCount = 0;
		ImageProcessor* processor = new ImageProcessor(_queue, _mutex, _condition, workIndexCount, this);
		workIndexCount++;
		processor->buildModelEngine(modelEnginePath, modelNamePath);
		processor->buildModelEngineOnnx(modelEnginePath, modelNamePath);
		processor->imageProcessingModuleIndex = index;
		connect(processor, &ImageProcessor::imageReady, this, &ImageProcessingModule::imageReady, Qt::QueuedConnection);
		_processors.push_back(processor);
		processor->start();
	}
}

ImageProcessingModule::ImageProcessingModule(int numConsumers, QObject* parent)
	: QObject(parent), _numConsumers(numConsumers) {
}

ImageProcessingModule::~ImageProcessingModule()
{
	// 通知所有线程退出
	for (auto processor : _processors) {
		processor->requestInterruption();
	}

	// 唤醒所有等待的线程
	{
		QMutexLocker locker(&_mutex);
		_condition.wakeAll();
	}

	// 等待所有线程退出
	for (auto processor : _processors) {
		if (processor->isRunning()) {
			processor->wait(1000); // 使用超时机制，等待1秒
		}
		delete processor;
	}
}

void ImageProcessingModule::onFrameCaptured(cv::Mat frame, float location, size_t index)
{
	if (frame.empty()) {
		return; // 跳过空帧
	}

	QMutexLocker locker(&_mutex);
	MatInfo mat;
	mat.image = frame;
	mat.location = location;
	mat.index = index;
	_queue.enqueue(mat);
	_condition.wakeOne();
}

QColor ImagePainter::ColorToQColor(Color c)
{
	switch (c) {
	case Color::White:   return QColor(255, 255, 255);
	case Color::Red:     return QColor(255, 0, 0);
	case Color::Green:   return QColor(0, 255, 0);
	case Color::Blue:    return QColor(0, 0, 255);
	case Color::Yellow:  return QColor(255, 255, 0);
	case Color::Cyan:    return QColor(0, 255, 255);
	case Color::Magenta: return QColor(255, 0, 255);
	case Color::Black:   return QColor(0, 0, 0);
	default:             return QColor(255, 255, 255);
	}
}

void ImagePainter::drawTextOnImage(QImage& image, const QVector<QString>& texts, const QVector<Color>& colorList, double proportion)
{
	if (texts.isEmpty() || proportion <= 0.0 || proportion > 1.0) {
		return; // 无效输入直接返回
	}

	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing);

	// 计算字体大小
	int imageHeight = image.height();
	int fontSize = static_cast<int>(imageHeight * proportion); // 字号由 proportion 决定

	QFont font = painter.font();
	font.setPixelSize(fontSize);
	painter.setFont(font);

	// 起始位置
	int x = 0;
	int y = 0;

	// 绘制每一行文字
	for (int i = 0; i < texts.size(); ++i) {
		// 获取颜色
		QColor color = (i < colorList.size()) ? ColorToQColor(colorList[i]) : ColorToQColor(colorList.last());
		painter.setPen(color);

		// 绘制文字
		painter.drawText(x, y + fontSize, texts[i]);

		// 更新 y 坐标
		y += fontSize; // 每行文字的间距等于字体大小
	}

	painter.end();
}

void ImagePainter::drawCirclesOnImage(cv::Mat& image, const std::vector<rw::imeot::ProcessRectanglesResultOT>& rectangles)
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
		cv::Scalar color(0, 165, 255);

		// 在图像上绘制圆
		cv::circle(image, cv::Point(centerX, centerY), radius, color, 5); // 2 表示线宽
	}
}