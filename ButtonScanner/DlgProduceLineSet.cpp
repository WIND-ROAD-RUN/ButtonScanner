#include "stdafx.h"
#include "DlgProduceLineSet.h"

DlgProduceLineSet::DlgProduceLineSet(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgProduceLineSetClass())
{
    ui->setupUi(this);
}

DlgProduceLineSet::~DlgProduceLineSet()
{
    delete ui;
}

 
