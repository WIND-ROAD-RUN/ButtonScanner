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

    build_radioButton();
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
    QObject::connect(ui->rbtn_edgeDamageSimilarity, &QPushButton::clicked,
        this, &DlgProductSet::rbtn_edgeDamageSimilarity_clicked);
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
}

void DlgProductSet::pbtn_outsideDiameterDeviation_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_outsideDiameterDeviation, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_photography_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_photography, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_blowTime_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowTime, 2);
    numKeyBoard->exec();

}

void DlgProductSet::rbtn_edgeDamageSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->rbtn_edgeDamageSimilarity, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_outerRadius_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_outerRadius, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_innerRadius_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_innerRadius, 2);
    numKeyBoard->exec();

}

void DlgProductSet::ptn_holesCountValue_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->ptn_holesCountValue, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_brokenEyeSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_brokenEyeSimilarity, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_crackSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_crackSimilarity, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_apertureValue_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_apertureValue, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_apertureSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_apertureSimilarity, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_holeCenterDistanceValue_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_holeCenterDistanceValue, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_holeCenterDistanceSimilarity_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_holeCenterDistanceSimilarity, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_specifyColorDifferenceR_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_specifyColorDifferenceR, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_specifyColorDifferenceG_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_specifyColorDifferenceG, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_specifyColorDifferenceB_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_specifyColorDifferenceB, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_specifyColorDifferenceDeviation_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_specifyColorDifferenceDeviation, 2);
    numKeyBoard->exec();

}

void DlgProductSet::pbtn_largeColorDifferenceDeviation_clicked()
{
    auto numKeyBoard = new NumKeyBord(this, ui->pbtn_largeColorDifferenceDeviation, 2);
    numKeyBoard->exec();

}
