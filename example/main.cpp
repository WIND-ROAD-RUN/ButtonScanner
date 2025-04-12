//#include "example.h"
//#include <QtWidgets/QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    example w;
//    w.show();
//    return a.exec();
//}

#include <QImage>
#include <QPainter>
#include <QFont>
#include <vector>
#include <string>

#include"ImageSaveEngine.h"

void drawTextOnImage(QImage& image, const QVector<QString>& texts, const QVector<QColor>& colorList, double proportion) {
    if (texts.isEmpty() || proportion <= 0.0 || proportion > 1.0) {
        return; // 无效输入直接返回
    }

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // 计算绘制区域
    int imageWidth = image.width();
    int imageHeight = image.height();
    int rectHeight = static_cast<int>(imageHeight * proportion);
    QRect drawRect(0, 0, imageWidth, rectHeight);

    // 设置字体大小
    QFont font = painter.font();
    font.setPixelSize(rectHeight / texts.size()); // 根据文本数量动态调整字体大小
    painter.setFont(font);

    // 绘制每一行文本
    int lineHeight = rectHeight / texts.size();
    for (int i = 0; i < texts.size(); ++i) {
        // 获取颜色，循环使用 colorList
        QColor color = colorList.isEmpty() ? Qt::black : colorList[i % colorList.size()];
        painter.setPen(color);

        // 计算每行文本的绘制位置
        QRect textRect(0, i * lineHeight, imageWidth, lineHeight);
        painter.drawText(textRect, Qt::AlignCenter, texts[i]);
    }

    painter.end();
}

// 定义颜色枚举
int main() {
    QImage image(500, 500, QImage::Format_RGB32);
    image.fill(Qt::white);

    QVector<QString> texts = { "Hello", "World", "Qt" };
    QVector<QColor> colors = { Qt::red, Qt::green, Qt::blue };
    double proportion = 0.5;

    drawTextOnImage(image, texts, colors, proportion);

    // 保存结果
    image.save("output.png");
    return 0;
}