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

// 定义颜色枚举
enum class color {
    WHITE,
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    BLACK
};

// 将 color 枚举转换为 QColor
QColor colorToQColor(color c) {
    switch (c) {
    case color::WHITE:   return QColor(255, 255, 255);
    case color::RED:     return QColor(255, 0, 0);
    case color::GREEN:   return QColor(0, 255, 0);
    case color::BLUE:    return QColor(0, 0, 255);
    case color::YELLOW:  return QColor(255, 255, 0);
    case color::CYAN:    return QColor(0, 255, 255);
    case color::MAGENTA: return QColor(255, 0, 255);
    case color::BLACK:   return QColor(0, 0, 0);
    default:             return QColor(255, 255, 255); // 默认白色
    }
}

void drawTextOnImage(QImage& image, const std::vector<std::string>& texts, const std::vector<color>& colorList, double proportion) {
    // 确保图像非空
    if (image.isNull() || texts.empty() || proportion <= 0.0 || proportion > 1.0) {
        return;
    }

    // 创建 QPainter
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // 计算字体大小和初始位置
    int imageHeight = image.height();
    int textAreaHeight = static_cast<int>(imageHeight * proportion); // 根据比例计算文字区域高度
    int yOffset = 10; // 初始Y偏移量

    // 动态调整字体大小
    QFont font("Arial");
    int fontSize = 20; // 初始字体大小
    font.setPixelSize(fontSize);
    painter.setFont(font);

    // 计算动态字体大小
    for (const auto& text : texts) {
        QRect textRect(0, 0, image.width(), textAreaHeight);
        QFontMetrics metrics(font);
        if (metrics.height() * texts.size() > textAreaHeight) {
            fontSize = static_cast<int>(fontSize * 0.9); // 缩小字体
            font.setPixelSize(fontSize);
            painter.setFont(font);
        }
    }

    // 绘制文字
    for (size_t i = 0; i < texts.size(); ++i) {
        // 确定颜色
        color textColor = color::WHITE; // 默认白色
        if (!colorList.empty()) {
            if (i < colorList.size()) {
                textColor = colorList[i];
            }
            else {
                textColor = colorList.back(); // 使用最后一个颜色
            }
        }

        // 设置颜色
        painter.setPen(colorToQColor(textColor));

        // 绘制文字
        QString qText = QString::fromStdString(texts[i]);
        painter.drawText(10, yOffset + fontSize, qText); // 左上角偏移量为 (10, yOffset)
        yOffset += fontSize + 5; // 行间距
    }

    painter.end();
}

int main() {
    // 创建一个示例图像
    QImage image(600, 400, QImage::Format_RGB32);
    image.fill(Qt::black);

    // 要绘制的文字
    std::vector<std::string> texts = {
        "没找到外径!",
        "This is a test.",
        "Dynamic font scaling.",
        "Hello, QImage!"
    };

    // 定义颜色列表
    std::vector<color> colorList = { color::RED, color::GREEN, color::YELLOW, color::CYAN };

    // 调用函数绘制文字
    drawTextOnImage(image, texts, colorList, 0.78);

    // 保存结果到文件
    image.save("output.png");

    return 0;
}