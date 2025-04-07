#include "stdafx.h"
#include "DlgProduceLineSet.h"

#include"NumKeyBord.h"

DlgProduceLineSet::DlgProduceLineSet(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgProduceLineSetClass())
{
    ui->setupUi(this);

    build_ui();
    build_connect();
}

DlgProduceLineSet::~DlgProduceLineSet()
{
    delete ui;
}

void DlgProduceLineSet::build_ui()
{
}

void DlgProduceLineSet::build_connect()
{
    QObject::connect(ui->pbtn_blowDistance1, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_blowDistance1_clicked);

}

void DlgProduceLineSet::pbtn_blowDistance1_clicked()
{
    auto numKeyBoard = new NumKeyBord(this,ui->pbtn_blowDistance1,2);
    numKeyBoard->setWindowModality(Qt::ApplicationModal);
    numKeyBoard->show();
}
