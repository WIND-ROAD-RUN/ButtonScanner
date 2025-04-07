#include "stdafx.h"

#include "ButtonScanner.h"
#include"DlgProductSet.h"
#include"DlgProduceLineSet.h"

#include"rqw_CameraObjectThread.hpp"
#include"hoec_CameraException.hpp"

#include"GlobalStruct.h"

#include<qdebug>
#include<QtConcurrent>
#include <future>
#define LOG(msg) qDebug() << "[" << __FILE__ << ":" << __LINE__ << "] INFO:" << msg

ButtonScanner::ButtonScanner(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::ButtonScannerClass())
{
	ui->setupUi(this);

	build_ui();
	build_connect();
	build_Motion();

	build_camera();
	start_monitor();

	//监视相机运动控制卡线程
	build_MonitoringThread();

	disp_Label.append(ui->label_imgDisplay);
	disp_Label.append(ui->label_imgDisplay_2);
	disp_Label.append(ui->label_imgDisplay_3);
	disp_Label.append(ui->label_imgDisplay_4);



	LOG()  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";


}

ButtonScanner::~ButtonScanner()
{
	delete ui;
}

void ButtonScanner::set_radioButton()
{
	ui->rbtn_debug->setAutoExclusive(false);
	ui->rbtn_defect->setAutoExclusive(false);
	ui->rbtn_downLight->setAutoExclusive(false);
	ui->rbtn_ForAndAgainst->setAutoExclusive(false);
	ui->rbtn_removeFunc->setAutoExclusive(false);
	ui->rbtn_sideLight->setAutoExclusive(false);
	ui->rbtn_takePicture->setAutoExclusive(false);
	ui->rbtn_upLight->setAutoExclusive(false);
}

void ButtonScanner::build_ui()
{
	//Set RadioButton ,make sure these can be checked at the same time
	set_radioButton();
}

void ButtonScanner::build_connect()
{
	QObject::connect(ui->pbtn_exit, &QPushButton::clicked, this, &ButtonScanner::pbtn_exit_clicked);

	QObject::connect(ui->pbtn_set, &QPushButton::clicked, this, &ButtonScanner::pbtn_set_clicked);

	QObject::connect(ui->pbtn_newProduction, &QPushButton::clicked, this, &ButtonScanner::pbtn_newProduction_clicked);
}

void ButtonScanner::build_camera()
{
	auto isTargetCamera = [](const QString& cameraIndex, const QString& targetName) {
		QRegularExpression regex(R"((\d+)\.(\d+)\.(\d+)\.(\d+))");
		QRegularExpressionMatch match = regex.match(targetName);

		if (match.hasMatch()) {
			auto matchString = match.captured(3);

			return cameraIndex == matchString;
		}

		return false;
	};


	auto cameraMetaDataCheck =
		[isTargetCamera](const QString& cameraIndex, const QVector<rw::rqw::CameraMetaData>& cameraInfo) {
		for (const auto& cameraMetaData : cameraInfo) {
			if (isTargetCamera(cameraIndex, cameraMetaData.ip)) {
				return cameraMetaData;
			}
		}
		rw::rqw::CameraMetaData error;
		error.ip = "0";
		return error;
	};

	auto cameraList = rw::rqw::CheckCameraList();

	{
		QString cameraIp1 = "11";
		auto cameraMetaData1 = cameraMetaDataCheck(cameraIp1, cameraList);

		if (cameraMetaData1.ip != "0") {
			try
			{
				_camera1 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
				_camera1->initCamera(cameraMetaData1, rw::rqw::CameraObjectTrigger::Hardware);
				QObject::connect(_camera1.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera1Display, Qt::DirectConnection);
			}
			catch (const std::exception&)
			{
				LOG()  "Camera 1 initialization failed.";
			}

		}
	}



	{
	    QString cameraIp2 = "12";
	    auto cameraMetaData2 = cameraMetaDataCheck(cameraIp2, cameraList);

	    if (cameraMetaData2.ip != "0") {
	        try
	        {
	            _camera2 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
	            _camera2->initCamera(cameraMetaData2, rw::rqw::CameraObjectTrigger::Hardware);
	            QObject::connect(_camera2.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera2Display, Qt::DirectConnection);
	        }
	        catch (const std::exception&)
	        {
	            LOG()  "Camera 2 initialization failed.";
	        }

	    }
	}

	{
	    QString cameraIp3 = "13";
	    auto cameraMetaData3 = cameraMetaDataCheck(cameraIp3, cameraList);
	    if (cameraMetaData3.ip != "0") {
	        try
	        {
	            _camera3 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
	            _camera3->initCamera(cameraMetaData3, rw::rqw::CameraObjectTrigger::Hardware);
	            QObject::connect(_camera3.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera3Display, Qt::DirectConnection);
	        }
	        catch (const std::exception&)
	        {
	            LOG()  "Camera 3 initialization failed.";
	        }
	    }
	}
	{
	    QString cameraIp4 = "14";
	    auto cameraMetaData4 = cameraMetaDataCheck(cameraIp4, cameraList);
	    if (cameraMetaData4.ip != "0") {
	        try
	        {
	            _camera4 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
	            _camera4->initCamera(cameraMetaData4, rw::rqw::CameraObjectTrigger::Hardware);
	            QObject::connect(_camera4.get(), &rw::rqw::CameraPassiveThread::frameCaptured, this, &ButtonScanner::_camera4Display, Qt::DirectConnection);
	        }
	        catch (const std::exception&)
	        {
	            LOG()  "Camera 4 initialization failed.";
	        }
	    }
	}





}

void ButtonScanner::start_monitor()
{
	if (_camera1)
	{
		try
		{
			_camera1->startMonitor();
		}
		catch (rw::hoec::CameraMonitorError& e)
		{
			LOG()  "Camera 1 startMonitor failed: " << e.what();
		}

	}
	if (_camera2)
	{
		try
		{
			_camera2->startMonitor();
		}
		catch (rw::hoec::CameraMonitorError& e)
		{
			LOG()  "Camera 2 startMonitor failed: " << e.what();
		}
	}
	if (_camera3)
	{
		try
		{
			_camera3->startMonitor();
		}
		catch (const rw::hoec::CameraMonitorError& e)
		{
			LOG()  "Camera 3 startMonitor failed: " << e.what();
		}
	}
	if (_camera4)
	{
		try
		{
			_camera4->startMonitor();
		}
		catch (const rw::hoec::CameraMonitorError& e)
		{
			LOG()  "Camera 4 startMonitor failed: " << e.what();
		}
	}
}
//初始化运动控制卡
void ButtonScanner::build_Motion()
{
	//这里获取全局变量
	auto& globalStruct = GlobalStruct::getInstance();

	//获取Zmotion
	auto& motionPtr = globalStruct.motionPtr;

	//下面通过motionPtr进行操作
	motionPtr.get()->OpenBoard((char*)"192.168.0.11");

}

void ButtonScanner::build_MonitoringThread()
{
	//线程内部
	QFuture<void>  m_monitorFuture = QtConcurrent::run([this]() {

		while (mark_Thread)
		{

			//运动控制卡实时状态
			{
				//这里获取全局变量
				auto& globalStruct = GlobalStruct::getInstance();

				//获取Zmotion
				auto& motionPtr = globalStruct.motionPtr;

				bool  boardState = motionPtr.get()->getBoardState();
				if (boardState == false)
				{
					motionPtr.get()->OpenBoard((char*)"192.168.0.11");

				}
				else
				{

				}
			}
			//获得相机链接状态
			{






			}

			QThread::msleep(500);



		}





	});


}

//监控io点位线程
void ButtonScanner::build_IOThread()
{
	//线程内部
	QFuture<void>  m_monitorFuture = QtConcurrent::run([this]() {
		//这里获取全局变量
		auto& globalStruct = GlobalStruct::getInstance();

		//获取Zmotion
		auto& motionPtr = globalStruct.motionPtr;
		while (mark_Thread)
		{

			bool state = false;
			state = motionPtr->GetIOIn(2);
			//急停

			if (state == true)
			{
				// pidaimove->stop();
				motionPtr->StopAllAxis();
				motionPtr->SetIOOut(1, false);
				
				motionPtr->SetIOOut(7, false);

			}
			//else
			//{
			//	//开始按钮
			//	bool state = false;
			//	state = motionPtr->GetIOIn(1);
			//	//启动程序
			//	if (state == true)
			//	{


			//		//所有电机上电
			//		QtConcurrent::run([this, &motionPtr]() {
			//			QThread::msleep(500);
			//			motionPtr->SetIOOut(1, true);
			//			//启动电机
   //                 motionPtr->SetAxisType(0,1);
   //                 double unit= GlobelParam::SystemParam[9].toDouble();
   //                 motionPtr->SetAxisPulse(0,unit);
   //                 double acc=GlobelParam::SystemParam[10].toDouble();
   //                 motionPtr->SetAxisAcc(0,acc);
   //                 motionPtr->SetAxisDec(0,acc);
   //                 double speed= GlobelParam::SystemParam[8].toDouble();
   //                 motionPtr->SetAxisRunSpeed(0,speed);
   //                 // pidaimove->start(100);
   //                 motionPtr->AxisRun(0,-1);
   //                 motionPtr->SetIOOut(7,true);
			//		});
			//	}
			//	else
			//	{







			//	}





			//}


















		}


	});

}









QImage ButtonScanner::cvMatToQImage(const cv::Mat& mat)
{
	if (mat.type() == CV_8UC1) {
		return QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_Grayscale8);
	}
	else if (mat.type() == CV_8UC3) {
		return QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_RGB888).rgbSwapped();
	}
	else if (mat.type() == CV_8UC4) {
		return QImage(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_RGBA8888);
	}
	else {
		LOG()  "Unsupported image format";
		return QImage();
	}

}




cv::Mat ButtonScanner::longRunningTask(const cv::Mat& frame,int workindex) {


	try {
		// 1. 快速克隆输入帧（避免后续操作修改原数据）
		cv::Mat result = frame.clone();
		auto& globalStruct = GlobalStruct::getInstance();

		
		std::unique_ptr<rw::ime::ModelEngine>* modelEngine=nullptr;
		if (workindex==0)
		{
			modelEngine = &globalStruct.modelEnginePtr1;
		}
		if (workindex == 1)
		{
			modelEngine = &globalStruct.modelEnginePtr2;
		}
		if (workindex == 2)
		{
			modelEngine = &globalStruct.modelEnginePtr3;
		}
		if (workindex == 3)
		{
			modelEngine = &globalStruct.modelEnginePtr4;
		}

		// 3. 处理模型推理
		cv::Mat ResultMat;
		cv::Mat MaskMat;
		std::vector<rw::ime::ProcessRectanglesResult> resultRectangles;

		// 4. 性能计时（使用高精度时钟）
		static auto lastCallTime = std::chrono::steady_clock::now();
		auto startTime = std::chrono::steady_clock::now();
		modelEngine->get()->ProcessMask(result, ResultMat, MaskMat, resultRectangles);

		auto endTime = std::chrono::steady_clock::now();
		auto timeDiff = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - lastCallTime).count();
		lastCallTime = startTime; // 更新为本次调用的开始时间

		LOG()  "Model processing time: "
			<< std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()
			<< " ms | Interval since last call: " << timeDiff << " ms";
		//QImage image = cvMatToQImage(result);
		// 5. 安全更新UI（检查对象存活性）
		/*if (QThread::currentThread() != this->thread()) {
			QMetaObject::invokeMethod(this, [this, result, image, workindex]() {

				

				if (!this->ui || !disp_Label[workindex]) return;

				
				if (!image.isNull()) {
					disp_Label[workindex]->setPixmap(QPixmap::fromImage(image.scaled(
						disp_Label[workindex]->size(),
						Qt::KeepAspectRatio,
						Qt::SmoothTransformation
					)));
				}
				else {
					LOG()  "Failed to convert cv::Mat to QImage";
				}
			}, Qt::QueuedConnection);
		}
		*/

		return ResultMat;
	}
	catch (const std::exception& e) {
		LOG()  "Error in longRunningTask1: " << e.what();
		return cv::Mat(); // 返回空矩阵表示错误
	}
}



void ButtonScanner::_camera1Display(cv::Mat frame)
{
	static size_t frameCount = 0;
	//LOG()  "Camera 1 frame count: " << ++frameCount;




	QFuture<void>  m_monitorFuture = QtConcurrent::run([this, frame]() {


		longRunningTask(frame,0);




	});

	
}
void ButtonScanner::_camera2Display(cv::Mat frame)
{
	static size_t frameCount = 0;
	//LOG()  "Camera 2 frame count: " << ++frameCount;

	QFuture<void>  m_monitorFuture = QtConcurrent::run([this, frame]() {


		longRunningTask(frame, 1);




	});
}
void ButtonScanner::_camera3Display(cv::Mat frame)
{
	static size_t frameCount = 0;
	//LOG()  "Camera 3 frame count: " << ++frameCount;
	QFuture<void>  m_monitorFuture = QtConcurrent::run([this, frame]() {


		longRunningTask(frame, 2);




	});
}
void ButtonScanner::_camera4Display(cv::Mat frame)
{
	static size_t frameCount = 0;
	//LOG()  "Camera 4 frame count: " << ++frameCount;

	QFuture<void>  m_monitorFuture = QtConcurrent::run([this, frame]() {


		longRunningTask(frame, 3);




	});
}
void ButtonScanner::pbtn_set_clicked()
{
	DlgProduceLineSet dlgProduceLineSet;
	dlgProduceLineSet.exec();
}

void ButtonScanner::pbtn_newProduction_clicked()
{
	DlgProductSet dlgProductSet;
	dlgProductSet.exec();
}

void ButtonScanner::pbtn_exit_clicked()
{
	//TODO: question messagebox
	this->close();
}
