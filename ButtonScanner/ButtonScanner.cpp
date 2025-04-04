#include "stdafx.h"
#include "ButtonScanner.h"
#include"DlgProductSet.h"
#include"DlgProduceLineSet.h"

ButtonScanner::ButtonScanner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ButtonScannerClass())
{
    ui->setupUi(this);

    build_ui();
    build_connect();
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
    QObject::connect(ui->pbtn_exit,&QPushButton::clicked,this, &ButtonScanner::pbtn_exit_clicked);

    QObject::connect(ui->pbtn_set, &QPushButton::clicked, this, &ButtonScanner::pbtn_set_clicked);

    QObject::connect(ui->pbtn_newProduction, &QPushButton::clicked, this, &ButtonScanner::pbtn_newProduction_clicked);
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
