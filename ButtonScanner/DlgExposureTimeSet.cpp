#include "stdafx.h"
#include "DlgExposureTimeSet.h"

#include"NumKeyBord.h"

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
}

void DlgExposureTimeSet::build_connect()
{
    QObject::connect(ui->pbtn_exposureTimeValue,&QPushButton::clicked,
        this,&DlgExposureTimeSet::pbtn_exposureTimeValue_clicked);
}

void DlgExposureTimeSet::pbtn_exposureTimeValue_clicked()
{
    auto numKeyBord = new NumKeyBord(this,ui->pbtn_exposureTimeValue,1);
    numKeyBord->exec();
    delete numKeyBord;

}
