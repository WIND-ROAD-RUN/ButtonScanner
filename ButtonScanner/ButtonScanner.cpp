#include "stdafx.h"

#include"rqw_CameraObjectThread.hpp"
#include"hoec_CameraException.hpp"

#include "ButtonScanner.h"
#include"DlgProductSet.h"
#include"DlgProduceLineSet.h"
#include"GlobalStruct.h"

#include<qdebug>
#include<QtConcurrent>
#include <future>
#include<QDir>
#include<QFileInfo>

ButtonScanner::ButtonScanner(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::ButtonScannerClass())
{
	ui->setupUi(this);

	build_ui();
	build_connect();

	build_Motion();

	build_camera();

    build_ImageProcessorModule();

	//监视相机运动控制卡线程
	build_MonitoringThread();

	start_monitor();
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
	auto& globalStruct = GlobalStruct::getInstance();
	globalStruct.cameraIp1 = "11";
    globalStruct.cameraIp2 = "12";
    globalStruct.cameraIp3 = "13";
    globalStruct.cameraIp4 = "14";

    globalStruct.buildCamera();
}

void ButtonScanner::build_ImageProcessorModule()
{
	auto& globalStruct = GlobalStruct::getInstance();

	//
	QString enginePath = R"(model/model.engine)";
	QString namePath = R"(model/index.names)";
	QDir dir;

	QString enginePathFull = dir.absoluteFilePath(enginePath);
	QString namePathFull = dir.absoluteFilePath(namePath);

	QFileInfo engineFile(enginePathFull);
	QFileInfo nameFile(namePathFull);

	if (!engineFile.exists() || !nameFile.exists()) {
		QMessageBox::critical(this, "Error", "Engine file or Name file does not exist. The application will now exit.");
		QApplication::quit();
		return;
	}



	//TODO：使用对话框提示用户

	
	globalStruct.enginePath = enginePathFull;
	globalStruct.namePath = namePathFull;

    globalStruct.buildImageProcessingModule(2);

    ////连接界面显示和图像处理模块
    QObject::connect(globalStruct._imageProcessingModule1.get(), &ImageProcessingModule::imageReady,
       this, &ButtonScanner::_camera1Display, Qt::DirectConnection);
    QObject::connect(globalStruct._imageProcessingModule2.get(), &ImageProcessingModule::imageReady,
        this, &ButtonScanner::_camera2Display, Qt::DirectConnection);
    QObject::connect(globalStruct._imageProcessingModule3.get(), &ImageProcessingModule::imageReady,
        this, &ButtonScanner::_camera3Display, Qt::DirectConnection);
    QObject::connect(globalStruct._imageProcessingModule4.get(), &ImageProcessingModule::imageReady,
        this, &ButtonScanner::_camera4Display, Qt::DirectConnection);

}

void ButtonScanner::start_monitor()
{
	auto& globalStruct = GlobalStruct::getInstance();
	globalStruct.startMonitor();
}

void ButtonScanner::build_Motion()
{
	auto& globalStruct = GlobalStruct::getInstance();

	globalStruct.buildMotion();

	//获取Zmotion
	auto& motionPtr = globalStruct._motionPtr;

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
				auto& motionPtr = globalStruct._motionPtr;

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

void ButtonScanner::build_IOThread()
{
	//线程内部
	QFuture<void>  m_monitorFuture = QtConcurrent::run([this]() {
		//这里获取全局变量
		auto& globalStruct = GlobalStruct::getInstance();

		//获取Zmotion
		auto& motionPtr = globalStruct._motionPtr;
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

void ButtonScanner::_camera1Display(QImage image)
{
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label_imgDisplay->setPixmap(pixmap.scaled(ui->label_imgDisplay->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
	
}

void ButtonScanner::_camera2Display(QImage image)
{
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->label_imgDisplay_2->setPixmap(pixmap.scaled(ui->label_imgDisplay_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ButtonScanner::_camera3Display(QImage image)
{
	QPixmap pixmap = QPixmap::fromImage(image);
	ui->label_imgDisplay_3->setPixmap(pixmap.scaled(ui->label_imgDisplay_3->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

}

void ButtonScanner::_camera4Display(QImage image)
{
	QPixmap pixmap = QPixmap::fromImage(image);
	ui->label_imgDisplay_4->setPixmap(pixmap.scaled(ui->label_imgDisplay_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

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
	auto& globalStruct = GlobalStruct::getInstance();
	globalStruct.destroyCamera();
	globalStruct.destroyImageProcessingModule();
    globalStruct.destroyMotion();

	this->close();
}
