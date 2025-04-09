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
    delete ui;
}

void DlgExposureTimeSet::build_ui()
{
    auto& globalStruct = GlobalStruct::getInstance();
    auto& exposureTimeSetConfig = globalStruct.dlgExposureTimeSetConfig;
    ui->pbtn_exposureTimeValue->setText(QString::number(exposureTimeSetConfig.expousureTime));
}

void DlgExposureTimeSet::build_connect()
{
    QObject::connect(ui->pbtn_exposureTimeValue,&QPushButton::clicked,
        this,&DlgExposureTimeSet::pbtn_exposureTimeValue_clicked);
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

    auto& globalStruct = GlobalStruct::getInstance();
    globalStruct.dlgExposureTimeSetConfig.expousureTime = newValue;

    globalStruct.saveDlgExposureTimeSetConfig();

}
