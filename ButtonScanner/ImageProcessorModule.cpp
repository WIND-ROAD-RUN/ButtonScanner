#include"stdafx.h"
#include "GlobalStruct.h"
#include"ImageProcessorModule.h"
#include"StatisticalInfoComputingThread.h"
#include"ime_modelOnnxRuntime.h"
#include <QtConcurrent> 

void ImageProcessor::buildModelEngine(const QString& enginePath, const QString& namePath)
{
    _modelEnginePtr = std::make_unique<rw::ime::ModelEngine>(enginePath.toStdString(), namePath.toStdString());
}

void ImageProcessor::buildModelEngineOnnx(const QString& enginePath, const QString& namePath)
{
    _modelEnginePtrOnnx = std::make_unique<rw::ime::ModelEngineOnnxRuntime>(enginePath.toStdString(), namePath.toStdString());
}

cv::Mat ImageProcessor::processAI(MatInfo& frame, QVector<QString>& errorInfo, std::vector<rw::ime::ProcessRectanglesResult>& vecRecogResult)
{
    auto& globalStruct = GlobalStructData::getInstance();


    cv::Mat resultImage1;
    std::vector<rw::ime::ProcessRectanglesResultOnnx > vecRecogResultOnnx;
    // 使用 QtConcurrent::run 将 _modelEnginePtrOnnx->ProcessMask 放到后台线程中执行
    QFuture<void> onnxFuture = QtConcurrent::run([&]() {
        _modelEnginePtrOnnx->ProcessMask(frame.image, resultImage1, vecRecogResultOnnx);
        });

    cv::Mat resultImage;
    cv::Mat maskImage = cv::Mat::zeros(frame.image.size(), CV_8UC1);

    _modelEnginePtr->ProcessMask(frame.image, resultImage, maskImage, vecRecogResult);

    onnxFuture.waitForFinished();


    if (globalStruct.isOpenRemoveFunc || (globalStruct.isDebugMode)) {
        eliminationLogic(frame, resultImage, errorInfo, vecRecogResult);
    }

    return resultImage.clone();
}

void ImageProcessor::eliminationLogic(MatInfo& frame, cv::Mat& resultImage, QVector<QString>& errorInfo, std::vector<rw::ime::ProcessRectanglesResult>& processRectanglesResult)
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
        switch (processRectanglesResult[i].classId)
        {
        case 0: waiJingIndexs.push_back(i); continue;
        case 1: holesCount++; konJingIndexs.push_back(i);continue;
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
    for (const auto& item : processRectanglesResult) {
        if (item.classId == 0) {
            body.emplace_back(item);
        }
        else if (item.classId == 1) {
            hole.emplace_back(item);
        }
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
                     errorInfo.emplace_back("外径 " + QString::number(shangXiaPianCha * pixEquivalent));
                 else
                     errorInfo.emplace_back("外径 " + QString::number(zuoYouPianCha * pixEquivalent));
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

            if (score > checkConfig.edgeDamageSimilarity)
            {
                isBad = true;
                errorInfo.emplace_back("破边 " + QString::number(score));
            }
        }
    }

	//检查气孔
	if (checkConfig.poreEnable)
    {
        for (int i = 0; i < qiKonIndexs.size(); i++)
        {
            auto score = processRectanglesResult[qiKonIndexs[i]].score;
            if (score > 30)
            {
                isBad = true;
                errorInfo.emplace_back("气孔 " + QString::number(score));
            }
        }
    }

	//检查堵眼
	if (checkConfig.blockEyeEnable)
    {
        for (int i = 0; i < duYanIndexs.size(); i++)
        {
            auto score = processRectanglesResult[duYanIndexs[i]].score;
            if (score > 10)
            {
                isBad = true;
                errorInfo.emplace_back("堵眼 " + QString::number(score));
            }
        }
    }

	//检查磨石
	if (checkConfig.grindStoneEnable)
    {
        for (int i = 0; i < moShiIndexs.size(); i++)
        {
            auto score = processRectanglesResult[moShiIndexs[i]].score;
            if (score > 0)
            {
                isBad = true;
                errorInfo.emplace_back("磨石 " + QString::number(score));
            }
        }
    }

	//检查料头
    if (checkConfig.materialHeadEnable)
    {
        for (int i = 0; i < liaoTouIndexs.size(); i++)
        {
            auto score = processRectanglesResult[liaoTouIndexs[i]].score;
            if (score > 10)
            {
                isBad = true;
                errorInfo.emplace_back("料头 " + QString::number(score));
            }
        }
    }

	//检查脏污
    if (checkConfig.paintEnable)
	{
		for (int i = 0; i < youQiIndexs.size(); i++)
		{
		 auto score = processRectanglesResult[youQiIndexs[i]].score;
			if (score > 50)
			{
            isBad = true;
            errorInfo.emplace_back("油漆 " + QString::number(score));
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
            if (score > checkConfig.crackSimilarity)
            {
                isBad = true;
                errorInfo.emplace_back("裂痕 " + QString::number(score));
            }
        }
    }

	//检查小气孔

    if (checkConfig.brokenEyeEnable)
{
    for (int i = 0; i < poYanIndexs.size(); i++)
    {
        auto score = processRectanglesResult[poYanIndexs[i]].score;
        auto width = abs(processRectanglesResult[poYanIndexs[i]].right_bottom.first - processRectanglesResult[poYanIndexs[i]].left_top.first);
        auto height = abs(processRectanglesResult[poYanIndexs[i]].right_bottom.second - processRectanglesResult[poYanIndexs[i]].left_top.second);
        if (score > checkConfig.brokenEyeSimilarity)
        {
            isBad = true;
            errorInfo.emplace_back("破眼 " + QString::number(score));
        }
    }
}

	//检查小破边
    if (checkConfig.apertureEnable)
    {
        for (int i = 0; i < konJingIndexs.size(); i++)
        {
            auto shangXiaPianCha = processRectanglesResult[konJingIndexs[i]].right_bottom.second - processRectanglesResult[konJingIndexs[i]].left_top.second - checkConfig.apertureValue / pixEquivalent;
            auto zuoYouPianCha = processRectanglesResult[konJingIndexs[i]].right_bottom.first - processRectanglesResult[konJingIndexs[i]].left_top.first - checkConfig.apertureValue / pixEquivalent;

            auto shangXiaPianChaAbs = abs(shangXiaPianCha);
            auto zuoYouPianChaAbs = abs(zuoYouPianCha);

            if (shangXiaPianChaAbs > checkConfig.apertureSimilarity / pixEquivalent || zuoYouPianChaAbs > checkConfig.apertureSimilarity / pixEquivalent)
            {
                isBad = true;

                if (shangXiaPianChaAbs >= zuoYouPianChaAbs)
                    errorInfo.emplace_back("孔径 " + QString::number(shangXiaPianCha * pixEquivalent));

                else
                    errorInfo.emplace_back("孔径 " + QString::number(zuoYouPianCha * pixEquivalent));
            }
        }
    }

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

	//检查小气孔
    if (globalStruct.isOpenRemoveFunc) {
        if (isBad) {
            globalStruct.statisticalInfo.wasteCount++;
        }

        if (imageProcessingModuleIndex == 2 || imageProcessingModuleIndex == 4) {
            globalStruct.statisticalInfo.produceCount++;
        }

        if (isBad) {
            float absLocation = frame.location;
            if (absLocation<0) {
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

void ImageProcessor::drawErrorLocate(QImage& image, std::vector<rw::ime::ProcessRectanglesResult>& vecRecogResult)
{
    if (image.isNull()) {
        return;
    }
    int i = 0;
    for (const auto& item : vecRecogResult) {
        if (i == 0 || i == 1) {
            return;
        }
        auto leftTop = item.left_top;
        auto rightBottom = item.right_bottom;
        // 绘制矩形框
        QPainter painter(&image);
        painter.setPen(QPen(Qt::red, 2));
        painter.drawRect(QRect(leftTop.first, leftTop.second, rightBottom.first - leftTop.first, rightBottom.second - leftTop.second));
        // 绘制文字
        QString text;

        switch (item.classId)
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
            text = QString::number(item.classId);
            break;
        }
        painter.drawText(leftTop.first, leftTop.second - 5, text);
        ++i;
    }
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

        std::vector<rw::ime::ProcessRectanglesResult> vecRecogResult;

        // 开始计时
        auto startTime = std::chrono::high_resolution_clock::now();

        //预留处理时间的位子
        processInfo.emplace_back();

        // 调用 processAI 函数
        cv::Mat result = processAI(frame, processInfo, vecRecogResult);

        // 结束计时
        auto endTime = std::chrono::high_resolution_clock::now();

        // 计算耗时
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

		processInfo[0] = QString("处理时间: %1 ms").arg(duration);

        auto  image = cvMatToQImage(result);

        // 绘制错误信息
        ImagePainter::drawTextOnImage(image, processInfo, { ImagePainter::Color::Green,ImagePainter::Color::Red },0.8);

        // 绘制错误定位
        drawErrorLocate(image, vecRecogResult);

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
        Color textColor = Color::White; // 默认白色
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
        if (rect.classId != 1) {
            return;
        }
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