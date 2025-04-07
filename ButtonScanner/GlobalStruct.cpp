#include "stdafx.h"

#include "GlobalStruct.h"
#include"hoec_CameraException.hpp"
#include"rqw_CameraObjectThread.hpp"


void GlobalStruct::buildImageProcessingModule(size_t num)
{
    _imageProcessingModule1 = std::make_unique<ImageProcessingModule>(num,this);
    _imageProcessingModule2 = std::make_unique<ImageProcessingModule>(num,this);
    _imageProcessingModule3 = std::make_unique<ImageProcessingModule>(num,this);
    _imageProcessingModule4 = std::make_unique<ImageProcessingModule>(num,this);
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
				_camera1->initCamera(cameraMetaData1, rw::rqw::CameraObjectTrigger::Hardware);
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
				_camera2->initCamera(cameraMetaData2, rw::rqw::CameraObjectTrigger::Hardware);
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
				_camera3->initCamera(cameraMetaData3, rw::rqw::CameraObjectTrigger::Hardware);
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
				_camera4->initCamera(cameraMetaData4, rw::rqw::CameraObjectTrigger::Hardware);
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

void GlobalStruct::buildModelEngine()
{
    modelEnginePtr1 = std::make_unique<rw::ime::ModelEngine>(enginePath.toStdString(), namePath.toStdString());
	modelEnginePtr2 = std::make_unique<rw::ime::ModelEngine>(enginePath.toStdString(), namePath.toStdString());
	modelEnginePtr3 = std::make_unique<rw::ime::ModelEngine>(enginePath.toStdString(), namePath.toStdString());
	modelEnginePtr4 = std::make_unique<rw::ime::ModelEngine>(enginePath.toStdString(), namePath.toStdString());
}

void GlobalStruct::buildMotion()
{
	motionPtr = std::make_unique<zwy::scc::Motion>();
}

GlobalStruct::GlobalStruct()
{

}
