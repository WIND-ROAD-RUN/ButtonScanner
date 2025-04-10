#include "stdafx.h"
#include "DlgExposureTimeSet.h"

#include"NumKeyBord.h"
#include"GlobalStruct.h"

DlgExposureTimeSet::DlgExposureTimeSet(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgExposureTimeSetClass())
{
    ui->setupUi(this);
    build_connect();
    build_ui();
}

DlgExposureTimeSet::~DlgExposureTimeSet()
{
    ResetCamera();
    delete ui;
}

void DlgExposureTimeSet::build_ui()
{
    auto& globalStruct = GlobalStructData::getInstance();
    auto& exposureTimeSetConfig = globalStruct.dlgExposureTimeSetConfig;
    ui->pbtn_exposureTimeValue->setText(QString::number(exposureTimeSetConfig.expousureTime));
}

void DlgExposureTimeSet::build_connect()
{
    QObject::connect(ui->pbtn_exposureTimeValue,&QPushButton::clicked,
        this,&DlgExposureTimeSet::pbtn_exposureTimeValue_clicked);
}

void DlgExposureTimeSet::SetCamera()
{
    auto& globalStruct = GlobalStructData::getInstance();

    if (globalStruct.camera1) {
        globalStruct.camera1->setTriggerMode(rw::rqw::CameraObjectTrigger::Software);
        globalStruct.camera1->setFrameRate(5);
    }

    if (globalStruct.camera2) {
        globalStruct.camera2->setTriggerMode(rw::rqw::CameraObjectTrigger::Software);
        globalStruct.camera2->setFrameRate(5);
    }

    if (globalStruct.camera3) {
        globalStruct.camera3->setTriggerMode(rw::rqw::CameraObjectTrigger::Software);
        globalStruct.camera3->setFrameRate(5);
    }

    if (globalStruct.camera4) {
        globalStruct.camera4->setTriggerMode(rw::rqw::CameraObjectTrigger::Software);
        globalStruct.camera4->setFrameRate(5);
    }
}

void DlgExposureTimeSet::ResetCamera()
{
    auto& globalStruct = GlobalStructData::getInstance();

    if (globalStruct.camera1)
    {
        globalStruct.camera1->setTriggerMode(rw::rqw::CameraObjectTrigger::Hardware);
    }
    if (globalStruct.camera2)
    {
        globalStruct.camera2->setTriggerMode(rw::rqw::CameraObjectTrigger::Hardware);
    }
    if (globalStruct.camera3)
    {
        globalStruct.camera3->setTriggerMode(rw::rqw::CameraObjectTrigger::Hardware);
    }
    if (globalStruct.camera4)
    {
        globalStruct.camera4->setTriggerMode(rw::rqw::CameraObjectTrigger::Hardware);
    }

}

void DlgExposureTimeSet::pbtn_exposureTimeValue_clicked()
{
    auto olderValue=ui->pbtn_exposureTimeValue->text().toInt();
    auto numKeyBord = new NumKeyBord(this,ui->pbtn_exposureTimeValue,1);
    numKeyBord->exec();
    delete numKeyBord;

    auto newValue = ui->pbtn_exposureTimeValue->text().toInt();
    if (newValue<=0) {
        ui->pbtn_exposureTimeValue->setText(QString::number(olderValue));
        QMessageBox::warning(this, "错误", "曝光时间范围应设置为0~700");
        return;
    }
    if (newValue>700) {
        ui->pbtn_exposureTimeValue->setText(QString::number(olderValue));
        QMessageBox::warning(this, "错误", "曝光时间范围应设置为0~700");
        return;
    }
    if (newValue == olderValue) {
        return;
    }

    auto& globalStruct = GlobalStructData::getInstance();
    globalStruct.dlgExposureTimeSetConfig.expousureTime = newValue;

    globalStruct.setCameraExposureTime(1, newValue);
    globalStruct.setCameraExposureTime(2, newValue);
    globalStruct.setCameraExposureTime(3, newValue);
    globalStruct.setCameraExposureTime(4, newValue);


    globalStruct.saveDlgExposureTimeSetConfig();

}
