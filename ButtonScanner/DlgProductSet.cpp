#include "stdafx.h"
#include "DlgProductSet.h"

DlgProductSet::DlgProductSet(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DlgProductSetClass())
{
    ui->setupUi(this);
    build_ui();
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

void DlgProductSet::build_radioButton()
{
    ui->rbtn_poreEnable->setAutoExclusive(false);
    ui->rbtn_paintEnable->setAutoExclusive(false);
    ui->rbtn_grindStoneEnable->setAutoExclusive(false);
    ui->rbtn_blockEyeEnable->setAutoExclusive(false);

}
