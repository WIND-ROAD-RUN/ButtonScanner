#include "stdafx.h"

#include "GlobalStruct.h"
#include"hoec_CameraException.hpp"
#include"rqw_CameraObjectThread.hpp"


void GlobalStruct::buildImageProcessingModule(size_t num)
{
    _imageProcessingModule1 = std::make_unique<ImageProcessingModule>(num,this);
	_imageProcessingModule1->modelEnginePath = enginePath;
	_imageProcessingModule1->modelNamePath = namePath;
    _imageProcessingModule1->BuildModule();

    _imageProcessingModule2 = std::make_unique<ImageProcessingModule>(num,this);
	_imageProcessingModule2->modelEnginePath = enginePath;
	_imageProcessingModule2->modelNamePath = namePath;
    _imageProcessingModule2->BuildModule();

    _imageProcessingModule3 = std::make_unique<ImageProcessingModule>(num,this);
	_imageProcessingModule3->modelEnginePath = enginePath;
	_imageProcessingModule3->modelNamePath = namePath;
    _imageProcessingModule3->BuildModule();

    _imageProcessingModule4 = std::make_unique<ImageProcessingModule>(num,this);
    _imageProcessingModule4->modelEnginePath = enginePath;
    _imageProcessingModule4->modelNamePath = namePath;
    _imageProcessingModule4->BuildModule();

    //连接相机和图像处理模块
    QObject::connect(_camera1.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
        _imageProcessingModule1.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);
	QObject::connect(_imageProcessingModule1.get(), &ImageProcessingModule::onProcessResult,
		this, &GlobalStruct::onCamera1ImageReady,Qt::DirectConnection);

	QObject::connect(_camera2.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
		_imageProcessingModule2.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);
    QObject::connect(_imageProcessingModule2.get(), &ImageProcessingModule::onProcessResult,
        this, &GlobalStruct::onCamera2ImageReady, Qt::DirectConnection);

	QObject::connect(_camera3.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
		_imageProcessingModule3.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);
    QObject::connect(_imageProcessingModule3.get(), &ImageProcessingModule::onProcessResult,
		this, &GlobalStruct::onCamera3ImageReady, Qt::DirectConnection);

	QObject::connect(_camera4.get(), &rw::rqw::CameraPassiveThread::frameCaptured,
		_imageProcessingModule4.get(), &ImageProcessingModule::onFrameCaptured, Qt::DirectConnection);
	QObject::connect(_imageProcessingModule4.get(), &ImageProcessingModule::onProcessResult,
		this, &GlobalStruct::onCamera4ImageReady, Qt::DirectConnection);
}

void GlobalStruct::buildConfigManager(rw::oso::StorageType type)
{
	_StoreContext = std::make_unique<rw::oso::StorageContext>(type);
}

void GlobalStruct::ReadConfig()
{
	ReadMainWindowConfig();
	ReadDlgProduceLineSetConfig();
	ReadDlgProductSetConfig();
}

void GlobalStruct::ReadMainWindowConfig()
{
	auto loadMainWindowConfig = _StoreContext->load(mainwindowFilePath.toStdString());
	if (loadMainWindowConfig) {
		mainWindowConfig = *loadMainWindowConfig;
	}
	else {
		LOG()  "Load main window config failed.";
	}
}

void GlobalStruct::ReadDlgProduceLineSetConfig()
{
	auto loadDlgProduceLineSetConfig = _StoreContext->load(dlgProduceLineSetFilePath.toStdString());
	if (loadDlgProduceLineSetConfig) {
		dlgProduceLineSetConfig = *loadDlgProduceLineSetConfig;
	}
	else {
		LOG()  "Load main window config failed.";
	}
}

void GlobalStruct::ReadDlgProductSetConfig()
{
	auto loadDlgProductSetConfig = _StoreContext->load(dlgProductSetFilePath.toStdString());
	if (loadDlgProductSetConfig) {
		dlgProductSetConfig = *loadDlgProductSetConfig;
	}
	else {
		LOG()  "Load main window config failed.";
	}
}

void GlobalStruct::saveConfig()
{
	saveMainWindowConfig();
	saveDlgProduceLineSetConfig();
	saveDlgProductSetConfig();
}

void GlobalStruct::saveMainWindowConfig()
{
	_StoreContext->save(mainWindowConfig, mainwindowFilePath.toStdString());
}

void GlobalStruct::saveDlgProduceLineSetConfig()
{
	_StoreContext->save(dlgProduceLineSetConfig, dlgProduceLineSetFilePath.toStdString());

}

void GlobalStruct::saveDlgProductSetConfig()
{
	_StoreContext->save(dlgProductSetConfig, dlgProductSetFilePath.toStdString());

}

void GlobalStruct::buildCamera()
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
		auto cameraMetaData1 = cameraMetaDataCheck(cameraIp1, cameraList);

		if (cameraMetaData1.ip != "0") {
			try
			{
				_camera1 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
				_camera1->initCamera(cameraMetaData1, rw::rqw::CameraObjectTrigger::Hardware,2);
				_camera1->cameraIndex = 1;
			}
			catch (const std::exception&)
			{
				LOG()  "Camera 1 initialization failed.";
			}
		}
	}



	{
		auto cameraMetaData2 = cameraMetaDataCheck(cameraIp2, cameraList);

		if (cameraMetaData2.ip != "0") {
			try
			{
				_camera2 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
				_camera2->initCamera(cameraMetaData2, rw::rqw::CameraObjectTrigger::Hardware,4);
				_camera2->cameraIndex = 2;
			}
			catch (const std::exception&)
			{
				LOG()  "Camera 2 initialization failed.";
			}

		}
	}

	{
		auto cameraMetaData3 = cameraMetaDataCheck(cameraIp3, cameraList);
		if (cameraMetaData3.ip != "0") {
			try
			{
				_camera3 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
				_camera3->initCamera(cameraMetaData3, rw::rqw::CameraObjectTrigger::Hardware,6);
				_camera3->cameraIndex = 3;
			}
			catch (const std::exception&)
			{
				LOG()  "Camera 3 initialization failed.";
			}
		}
	}
	{
		auto cameraMetaData4 = cameraMetaDataCheck(cameraIp4, cameraList);
		if (cameraMetaData4.ip != "0") {
			try
			{
				_camera4 = std::make_unique<rw::rqw::CameraPassiveThread>(this);
				_camera4->initCamera(cameraMetaData4, rw::rqw::CameraObjectTrigger::Hardware,8);
				_camera4->cameraIndex = 4;

			}
			catch (const std::exception&)
			{
				LOG()  "Camera 4 initialization failed.";
			}
		}
	}
}

void GlobalStruct::startMonitor()
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


void GlobalStruct::destroyCamera()
{
    _camera1.reset();
    _camera2.reset();
    _camera3.reset();
    _camera4.reset();
}

void GlobalStruct::destroyImageProcessingModule()
{
    _imageProcessingModule1.reset();
    _imageProcessingModule2.reset();
    _imageProcessingModule3.reset();
    _imageProcessingModule4.reset();
}

GlobalStruct::GlobalStruct()
{
}

void GlobalStruct::onCamera1ImageReady(bool isOk, float location)
{
	if (!isOk) {
		productPriorityQueue1.insert(location, location);
	}
}

void GlobalStruct::onCamera2ImageReady(bool isOk, float location)
{
	if (!isOk) {
		productPriorityQueue2.insert(location, location);
	}
}

void GlobalStruct::onCamera3ImageReady(bool isOk, float location)
{
	if (!isOk) {
		productPriorityQueue3.insert(location, location);
	}
}

void GlobalStruct::onCamera4ImageReady(bool isOk, float location)
{
	if (!isOk) {
		productPriorityQueue4.insert(location, location);
	}
}

