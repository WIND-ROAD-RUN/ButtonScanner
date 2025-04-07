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
        QMessageBox::critical(this, "Error", "�޷�����ͼƬ��");
        return;
    }

    // ��ȡ QLabel ��ʵ����ʾ�ߴ�
    QSize labelSize = ui->label_pic->sizeHint();

    // ��ȡ�豸���ر���
    qreal pixelRatio = devicePixelRatioF();

    // �� QPixmap ���ŵ� QLabel ��ʵ����ʾ�ߴ磬�������ݺ��
    QPixmap scaledPixmap = pixmap.scaled(labelSize * pixelRatio, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // �����豸���ر���
    scaledPixmap.setDevicePixelRatio(pixelRatio);

    ui->label_pic->setPixmap(scaledPixmap);

    // ȷ�� QLabel �ڵ�����Сʱ�Զ�����ͼƬ
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
