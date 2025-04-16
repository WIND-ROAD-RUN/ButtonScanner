#include "stdafx.h"
#include "DlgProduceLineSet.h"

#include"NumKeyBord.h"
#include"GlobalStruct.h"

DlgProduceLineSet::DlgProduceLineSet(QWidget* parent)
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
    read_config();
}

void DlgProduceLineSet::read_config()
{
    auto& globalStruct = GlobalStructData::getInstance();
    ui->pbtn_blowDistance1->setText(QString::number(globalStruct.dlgProduceLineSetConfig.blowDistance1));
    ui->pbtn_blowDistance2->setText(QString::number(globalStruct.dlgProduceLineSetConfig.blowDistance2));
    ui->pbtn_blowDistance3->setText(QString::number(globalStruct.dlgProduceLineSetConfig.blowDistance3));
    ui->pbtn_blowDistance4->setText(QString::number(globalStruct.dlgProduceLineSetConfig.blowDistance4));
    ui->pbtn_blowTime1->setText(QString::number(globalStruct.dlgProduceLineSetConfig.blowTime1));
    ui->pbtn_blowTime2->setText(QString::number(globalStruct.dlgProduceLineSetConfig.blowTime2));
    ui->pbtn_blowTime3->setText(QString::number(globalStruct.dlgProduceLineSetConfig.blowTime3));
    ui->pbtn_blowTime4->setText(QString::number(globalStruct.dlgProduceLineSetConfig.blowTime4));
    ui->pbtn_pixelEquivalent1->setText(QString::number(globalStruct.dlgProduceLineSetConfig.pixelEquivalent1));
    ui->pbtn_pixelEquivalent2->setText(QString::number(globalStruct.dlgProduceLineSetConfig.pixelEquivalent2));
    ui->pbtn_pixelEquivalent3->setText(QString::number(globalStruct.dlgProduceLineSetConfig.pixelEquivalent3));
    ui->pbtn_pixelEquivalent4->setText(QString::number(globalStruct.dlgProduceLineSetConfig.pixelEquivalent4));
    ui->pbtn_limit1->setText(QString::number(globalStruct.dlgProduceLineSetConfig.limit1));
    ui->pbtn_limit2->setText(QString::number(globalStruct.dlgProduceLineSetConfig.limit2));
    ui->pbtn_limit3->setText(QString::number(globalStruct.dlgProduceLineSetConfig.limit3));
    ui->pbtn_limit4->setText(QString::number(globalStruct.dlgProduceLineSetConfig.limit4));
    ui->cbox_powerOn->setChecked(globalStruct.dlgProduceLineSetConfig.powerOn);
    ui->cbox_blowingEnable1->setChecked(globalStruct.dlgProduceLineSetConfig.blowingEnable1);
    ui->cbox_blowingEnable2->setChecked(globalStruct.dlgProduceLineSetConfig.blowingEnable2);
    ui->cbox_blowingEnable3->setChecked(globalStruct.dlgProduceLineSetConfig.blowingEnable3);
    ui->cbox_blowingEnable4->setChecked(globalStruct.dlgProduceLineSetConfig.blowingEnable4);
    ui->cbox_none->setChecked(globalStruct.dlgProduceLineSetConfig.none);
    ui->cbox_run->setChecked(globalStruct.dlgProduceLineSetConfig.run);
    ui->cbox_alarm->setChecked(globalStruct.dlgProduceLineSetConfig.alarm);
    ui->cbox_workstationProtection12->setChecked(globalStruct.dlgProduceLineSetConfig.workstationProtection12);
    ui->cbox_workstationProtection34->setChecked(globalStruct.dlgProduceLineSetConfig.workstationProtection34);
    ui->pbtn_motorSpeed->setText(QString::number(globalStruct.dlgProduceLineSetConfig.motorSpeed));
    ui->pbtn_beltReductionRatio->setText(QString::number(globalStruct.dlgProduceLineSetConfig.beltReductionRatio));
    ui->pbtn_accelerationAndDeceleration->setText(QString::number(globalStruct.dlgProduceLineSetConfig.accelerationAndDeceleration));
    ui->pbtn_minBrightness->setText(QString::number(globalStruct.dlgProduceLineSetConfig.minBrightness));
    ui->pbtn_maxBrightness->setText(QString::number(globalStruct.dlgProduceLineSetConfig.maxBrightness));
    ui->pbtn_codeWheel->setText(QString::number(globalStruct.dlgProduceLineSetConfig.codeWheel));
    ui->pbtn_pulseFactor->setText(QString::number(globalStruct.dlgProduceLineSetConfig.pulseFactor));
}

void DlgProduceLineSet::build_connect()
{
    QObject::connect(ui->pbtn_blowDistance1, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_blowDistance1_clicked);
    QObject::connect(ui->pbtn_blowDistance2, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_blowDistance2_clicked);
    QObject::connect(ui->pbtn_blowDistance3, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_blowDistance3_clicked);
    QObject::connect(ui->pbtn_blowDistance4, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_blowDistance4_clicked);
	QObject::connect(ui->pbtn_close, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_close_clicked);

    QObject::connect(ui->pbtn_blowTime1, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_blowTime1_clicked);
    QObject::connect(ui->pbtn_blowTime2, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_blowTime2_clicked);
    QObject::connect(ui->pbtn_blowTime3, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_blowTime3_clicked);
    QObject::connect(ui->pbtn_blowTime4, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_blowTime4_clicked);

    QObject::connect(ui->pbtn_pixelEquivalent1, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_pixelEquivalent1_clicked);
    QObject::connect(ui->pbtn_pixelEquivalent2, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_pixelEquivalent2_clicked);
    QObject::connect(ui->pbtn_pixelEquivalent3, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_pixelEquivalent3_clicked);
    QObject::connect(ui->pbtn_pixelEquivalent4, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_pixelEquivalent4_clicked);

    QObject::connect(ui->pbtn_limit1, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_limit1_clicked);
    QObject::connect(ui->pbtn_limit2, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_limit2_clicked);
    QObject::connect(ui->pbtn_limit3, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_limit3_clicked);
    QObject::connect(ui->pbtn_limit4, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_limit4_clicked);

    QObject::connect(ui->pbtn_minBrightness, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_minBrightness_clicked);
    QObject::connect(ui->pbtn_maxBrightness, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_maxBrightness_clicked);

    QObject::connect(ui->pbtn_motorSpeed, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_motorSpeed_clicked);
    QObject::connect(ui->pbtn_beltReductionRatio, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_beltReductionRatio_clicked);
    QObject::connect(ui->pbtn_accelerationAndDeceleration, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_accelerationAndDeceleration_clicked);

    QObject::connect(ui->cbox_powerOn, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_powerOn_checked);
    QObject::connect(ui->cbox_blowingEnable1, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_blowingEnable1_checked);
    QObject::connect(ui->cbox_blowingEnable2, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_blowingEnable2_checked);
    QObject::connect(ui->cbox_blowingEnable3, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_blowingEnable3_checked);
    QObject::connect(ui->cbox_blowingEnable4, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_blowingEnable4_checked);
    QObject::connect(ui->cbox_none, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_none_checked);
    QObject::connect(ui->cbox_run, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_run_checked);
    QObject::connect(ui->cbox_alarm, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_alarm_checked);
    QObject::connect(ui->cbox_workstationProtection12, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_workstationProtection12_checked);
    QObject::connect(ui->cbox_workstationProtection34, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_workstationProtection34_checked);
    QObject::connect(ui->cbox_debugMode, &QCheckBox::clicked,
        this, &DlgProduceLineSet::cbox_debugMode_checked);

    QObject::connect(ui->pbtn_codeWheel, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_codeWheel_clicked);
    QObject::connect(ui->pbtn_pulseFactor, &QPushButton::clicked,
        this, &DlgProduceLineSet::pbtn_pulseFactor_clicked);
}

float DlgProduceLineSet::get_blowTime()
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    auto outsideDiameterValue = GlobalStructData.dlgProductSetConfig.outsideDiameterValue;
    auto beltSpeed = GlobalStructData.dlgProduceLineSetConfig.motorSpeed;
    auto blowTime = outsideDiameterValue / beltSpeed * 1000 / 2;
    return blowTime;
}

void DlgProduceLineSet::updateBeltSpeed()
{
    ui->pbtn_motorSpeed->setText(QString::number(GlobalStructData::getInstance().dlgProduceLineSetConfig.motorSpeed));
}

void DlgProduceLineSet::pbtn_blowDistance1_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowDistance1, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowDistance1 = ui->pbtn_blowDistance1->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_blowTime1_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowTime1, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowTime1 = ui->pbtn_blowTime1->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_blowDistance2_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowDistance2, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowDistance2 = ui->pbtn_blowDistance2->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_blowTime2_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowTime2, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowTime2 = ui->pbtn_blowTime2->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_blowDistance3_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowDistance3, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowDistance3 = ui->pbtn_blowDistance3->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_blowTime3_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowTime3, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowTime3 = ui->pbtn_blowTime3->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_blowDistance4_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowDistance4, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowDistance4 = ui->pbtn_blowDistance4->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_blowTime4_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowTime4, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowTime4 = ui->pbtn_blowTime4->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_pixelEquivalent1_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_pixelEquivalent1, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.pixelEquivalent1 = ui->pbtn_pixelEquivalent1->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_pixelEquivalent2_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_pixelEquivalent2, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.pixelEquivalent2 = ui->pbtn_pixelEquivalent2->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_pixelEquivalent3_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_pixelEquivalent3, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.pixelEquivalent3 = ui->pbtn_pixelEquivalent3->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_pixelEquivalent4_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_pixelEquivalent4, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.pixelEquivalent4 = ui->pbtn_pixelEquivalent4->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_limit1_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_limit1, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.limit1 = ui->pbtn_limit1->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_limit2_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_limit2, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.limit2 = ui->pbtn_limit2->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_limit3_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_limit3, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.limit3 = ui->pbtn_limit3->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_limit4_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_limit4, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.limit4 = ui->pbtn_limit4->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_minBrightness_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_minBrightness, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.minBrightness = ui->pbtn_minBrightness->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_maxBrightness_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_maxBrightness, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.maxBrightness = ui->pbtn_maxBrightness->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_motorSpeed_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_motorSpeed, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.motorSpeed = ui->pbtn_motorSpeed->text().toDouble();

    delete numKeyBoard;

    get_blowTime();
}

void DlgProduceLineSet::pbtn_beltReductionRatio_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_beltReductionRatio, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.beltReductionRatio = ui->pbtn_beltReductionRatio->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_accelerationAndDeceleration_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_accelerationAndDeceleration, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.accelerationAndDeceleration = ui->pbtn_accelerationAndDeceleration->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_codeWheel_clicked() {
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_codeWheel, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.codeWheel = ui->pbtn_codeWheel->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_pulseFactor_clicked() {
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_pulseFactor, 2);
    numKeyBoard->exec();

    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.pulseFactor = ui->pbtn_pulseFactor->text().toDouble();

    delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_close_clicked()
{
	auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.saveDlgProduceLineSetConfig();
	this->close();
}

void DlgProduceLineSet::cbox_powerOn_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.powerOn = ischeck;
}

void DlgProduceLineSet::cbox_blowingEnable1_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowingEnable1 = ischeck;
}

void DlgProduceLineSet::cbox_blowingEnable2_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowingEnable2 = ischeck;
}

void DlgProduceLineSet::cbox_blowingEnable3_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowingEnable3 = ischeck;
}

void DlgProduceLineSet::cbox_blowingEnable4_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.blowingEnable4 = ischeck;
}

void DlgProduceLineSet::cbox_none_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.none = ischeck;
}

void DlgProduceLineSet::cbox_run_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.run = ischeck;
}

void DlgProduceLineSet::cbox_alarm_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.alarm = ischeck;
}

void DlgProduceLineSet::cbox_workstationProtection12_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.workstationProtection12 = ischeck;
}

void DlgProduceLineSet::cbox_workstationProtection34_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.workstationProtection34 = ischeck;
}

void DlgProduceLineSet::cbox_debugMode_checked(bool ischeck)
{
    auto& GlobalStructData = GlobalStructData::getInstance();
    GlobalStructData.dlgProduceLineSetConfig.debugMode = ischeck;
}