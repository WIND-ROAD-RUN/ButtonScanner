#include "stdafx.h"
#include "DlgProductSet.h"
#include"NumKeyBord.h"

#include "GlobalStruct.h"

DlgProductSet::DlgProductSet(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgProductSetClass())
{
    ui->setupUi(this);
    build_ui();
    build_connect();
}

DlgProductSet::~DlgProductSet()
{
    delete ui;
}

void DlgProductSet::build_ui()
{

    read_config();
    read_image();
    build_radioButton();
}

void DlgProductSet::read_config()
{
    auto& GlobalStruct = GlobalStruct::getInstance();
    ui->rbtn_outsideDiameterEnable->setChecked(GlobalStruct.dlgProductSetConfig.outsideDiameterEnable);
    ui->pbtn_outsideDiameterValue->setText(QString::number(GlobalStruct.dlgProductSetConfig.outsideDiameterValue));
    ui->pbtn_outsideDiameterDeviation->setText(QString::number(GlobalStruct.dlgProductSetConfig.outsideDiameterDeviation));
    ui->pbtn_photography->setText(QString::number(GlobalStruct.dlgProductSetConfig.photography));
    ui->pbtn_blowTime->setText(QString::number(GlobalStruct.dlgProductSetConfig.blowTime));
    ui->rbtn_edgeDamageEnable->setChecked(GlobalStruct.dlgProductSetConfig.edgeDamageEnable);
    ui->rbtn_edgeDamageSimilarity->setText(QString::number(GlobalStruct.dlgProductSetConfig.edgeDamageSimilarity));
    ui->rbtn_shieldingRangeEnable->setCheckable(GlobalStruct.dlgProductSetConfig.shieldingRangeEnable);
    ui->pbtn_outerRadius->setText(QString::number(GlobalStruct.dlgProductSetConfig.outerRadius));
    ui->pbtn_innerRadius->setText(QString::number(GlobalStruct.dlgProductSetConfig.innerRadius));
    ui->rbtn_poreEnable->setChecked(GlobalStruct.dlgProductSetConfig.poreEnable);
    ui->rbtn_paintEnable->setChecked(GlobalStruct.dlgProductSetConfig.paintEnable);
    ui->rbtn_holesCountEnable->setChecked(GlobalStruct.dlgProductSetConfig.holesCountEnable);
    ui->ptn_holesCountValue->setText(QString::number(GlobalStruct.dlgProductSetConfig.holesCountValue));
    ui->rbtn_brokenEyeEnable->setChecked(GlobalStruct.dlgProductSetConfig.brokenEyeEnable);
    ui->pbtn_brokenEyeSimilarity->setText(QString::number(GlobalStruct.dlgProductSetConfig.brokenEyeSimilarity));
    ui->rbtn_crackEnable->setChecked(GlobalStruct.dlgProductSetConfig.crackEnable);
    ui->pbtn_crackSimilarity->setText(QString::number(GlobalStruct.dlgProductSetConfig.crackSimilarity));
    ui->rbtn_apertureEnable->setChecked(GlobalStruct.dlgProductSetConfig.apertureEnable);
    ui->pbtn_apertureValue->setText(QString::number(GlobalStruct.dlgProductSetConfig.apertureValue));
    ui->pbtn_apertureSimilarity->setText(QString::number(GlobalStruct.dlgProductSetConfig.apertureSimilarity));
    ui->rbtn_specifyColorDifferenceEnable->setChecked(GlobalStruct.dlgProductSetConfig.specifyColorDifferenceEnable);
    ui->pbtn_specifyColorDifferenceR->setText(QString::number(GlobalStruct.dlgProductSetConfig.specifyColorDifferenceR));
    ui->pbtn_specifyColorDifferenceG->setText(QString::number(GlobalStruct.dlgProductSetConfig.specifyColorDifferenceG));
    ui->pbtn_specifyColorDifferenceB->setText(QString::number(GlobalStruct.dlgProductSetConfig.specifyColorDifferenceB));
    ui->rbtn_largeColorDifferenceEnable->setChecked(GlobalStruct.dlgProductSetConfig.largeColorDifferenceEnable);
    ui->pbtn_largeColorDifferenceDeviation->setText(QString::number(GlobalStruct.dlgProductSetConfig.largeColorDifferenceDeviation));
    ui->rbtn_grindStoneEnable->setChecked(GlobalStruct.dlgProductSetConfig.grindStoneEnable);
    ui->rbtn_blockEyeEnable->setChecked(GlobalStruct.dlgProductSetConfig.blockEyeEnable);
    ui->pbtn_holeCenterDistanceValue->setText(QString::number(GlobalStruct.dlgProductSetConfig.holeCenterDistanceValue));
    ui->rbtn_materialHeadEnable->setChecked(GlobalStruct.dlgProductSetConfig.materialHeadEnable);
}

void DlgProductSet::read_image()
{
    QString imagePath = ":/ButtonScanner/image/product.png";
    QPixmap pixmap(imagePath);

    if (pixmap.isNull()) {
        QMessageBox::critical(this, "Error", "无法加载图片。");
        return;
    }

    // 获取 QLabel 的实际显示尺寸
    QSize labelSize = ui->label_pic->sizeHint();

    // 获取设备像素比率
    qreal pixelRatio = devicePixelRatioF();

    // 将 QPixmap 缩放到 QLabel 的实际显示尺寸，并保持纵横比
    QPixmap scaledPixmap = pixmap.scaled(labelSize * pixelRatio, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 设置设备像素比率
    scaledPixmap.setDevicePixelRatio(pixelRatio);

    ui->label_pic->setPixmap(scaledPixmap);

    // 确保 QLabel 在调整大小时自动缩放图片
    ui->label_pic->setScaledContents(true);
}

void DlgProductSet::build_connect()
{
    QObject::connect(ui->pbtn_outsideDiameterValue, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_outsideDiameterValue_clicked);
    QObject::connect(ui->pbtn_outsideDiameterDeviation, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_outsideDiameterDeviation_clicked);
    QObject::connect(ui->pbtn_photography, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_photography_clicked);
    QObject::connect(ui->pbtn_blowTime, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_blowTime_clicked);
    QObject::connect(ui->pbtn_outerRadius, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_outerRadius_clicked);
    QObject::connect(ui->pbtn_innerRadius, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_innerRadius_clicked);
    QObject::connect(ui->ptn_holesCountValue, &QPushButton::clicked,
        this, &DlgProductSet::ptn_holesCountValue_clicked);
    QObject::connect(ui->pbtn_brokenEyeSimilarity, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_brokenEyeSimilarity_clicked);
    QObject::connect(ui->pbtn_crackSimilarity, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_crackSimilarity_clicked);
    QObject::connect(ui->pbtn_apertureValue, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_apertureValue_clicked);
    QObject::connect(ui->pbtn_apertureSimilarity, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_apertureSimilarity_clicked);
    QObject::connect(ui->pbtn_holeCenterDistanceValue, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_holeCenterDistanceValue_clicked);
    QObject::connect(ui->pbtn_holeCenterDistanceSimilarity, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_holeCenterDistanceSimilarity_clicked);
    QObject::connect(ui->pbtn_specifyColorDifferenceR, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_specifyColorDifferenceR_clicked);
    QObject::connect(ui->pbtn_specifyColorDifferenceG, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_specifyColorDifferenceG_clicked);
    QObject::connect(ui->pbtn_specifyColorDifferenceB, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_specifyColorDifferenceB_clicked);
    QObject::connect(ui->pbtn_specifyColorDifferenceDeviation, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_specifyColorDifferenceDeviation_clicked);
    QObject::connect(ui->pbtn_largeColorDifferenceDeviation, &QPushButton::clicked,
        this, &DlgProductSet::pbtn_largeColorDifferenceDeviation_clicked);
}

void DlgProductSet::build_radioButton()
{
    ui->rbtn_poreEnable->setAutoExclusive(false);
    ui->rbtn_paintEnable->setAutoExclusive(false);
    ui->rbtn_grindStoneEnable->setAutoExclusive(false);
    ui->rbtn_blockEyeEnable->setAutoExclusive(false);

}

void DlgProductSet::pbtn_outsideDiameterValue_clicked() {
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_outsideDiameterValue, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.outsideDiameterValue=ui->pbtn_outsideDiameterValue->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_outsideDiameterDeviation_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_outsideDiameterDeviation, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.outsideDiameterDeviation = ui->pbtn_outsideDiameterDeviation->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_photography_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_photography, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.photography = ui->pbtn_photography->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_blowTime_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowTime, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.blowTime = ui->pbtn_blowTime->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::rbtn_edgeDamageSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->rbtn_edgeDamageSimilarity, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.edgeDamageSimilarity = ui->rbtn_edgeDamageSimilarity->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_outerRadius_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_outerRadius, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.outerRadius = ui->pbtn_outerRadius->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_innerRadius_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_innerRadius, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.innerRadius = ui->pbtn_innerRadius->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::ptn_holesCountValue_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->ptn_holesCountValue, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.holesCountValue = ui->ptn_holesCountValue->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_brokenEyeSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_brokenEyeSimilarity, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.brokenEyeSimilarity = ui->pbtn_brokenEyeSimilarity->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_crackSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_crackSimilarity, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.crackSimilarity = ui->pbtn_crackSimilarity->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_apertureValue_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_apertureValue, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.apertureValue = ui->pbtn_apertureValue->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_apertureSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_apertureSimilarity, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.apertureSimilarity = ui->pbtn_apertureSimilarity->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_holeCenterDistanceValue_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_holeCenterDistanceValue, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.holeCenterDistanceValue = ui->pbtn_holeCenterDistanceValue->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_holeCenterDistanceSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_holeCenterDistanceSimilarity, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.holeCenterDistanceSimilarity = ui->pbtn_holeCenterDistanceSimilarity->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_specifyColorDifferenceR_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_specifyColorDifferenceR, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.specifyColorDifferenceR = ui->pbtn_specifyColorDifferenceR->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_specifyColorDifferenceG_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_specifyColorDifferenceG, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.specifyColorDifferenceG = ui->pbtn_specifyColorDifferenceG->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_specifyColorDifferenceB_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_specifyColorDifferenceB, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.specifyColorDifferenceB = ui->pbtn_specifyColorDifferenceB->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_specifyColorDifferenceDeviation_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_specifyColorDifferenceDeviation, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.specifyColorDifferenceDeviation = ui->pbtn_specifyColorDifferenceDeviation->text().toDouble();

    delete numKeyBoard;
}

void DlgProductSet::pbtn_largeColorDifferenceDeviation_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_largeColorDifferenceDeviation, 2);
    numKeyBoard->exec();

    auto& GlobalStruct = GlobalStruct::getInstance();
    GlobalStruct.dlgProductSetConfig.largeColorDifferenceDeviation = ui->pbtn_largeColorDifferenceDeviation->text().toDouble();

    delete numKeyBoard;
}
