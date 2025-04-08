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

// ������ɫö��
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

// �� color ö��ת��Ϊ QColor
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
    default:             return QColor(255, 255, 255); // Ĭ�ϰ�ɫ
    }
}

void drawTextOnImage(QImage& image, const std::vector<std::string>& texts, const std::vector<color>& colorList, double proportion) {
    // ȷ��ͼ��ǿ�
    if (image.isNull() || texts.empty() || proportion <= 0.0 || proportion > 1.0) {
        return;
    }

    // ���� QPainter
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);

    // ���������С�ͳ�ʼλ��
    int imageHeight = image.height();
    int textAreaHeight = static_cast<int>(imageHeight * proportion); // ���ݱ���������������߶�
    int yOffset = 10; // ��ʼYƫ����

    // ��̬���������С
    QFont font("Arial");
    int fontSize = 20; // ��ʼ�����С
    font.setPixelSize(fontSize);
    painter.setFont(font);

    // ���㶯̬�����С
    for (const auto& text : texts) {
        QRect textRect(0, 0, image.width(), textAreaHeight);
        QFontMetrics metrics(font);
        if (metrics.height() * texts.size() > textAreaHeight) {
            fontSize = static_cast<int>(fontSize * 0.9); // ��С����
            font.setPixelSize(fontSize);
            painter.setFont(font);
        }
    }

    // ��������
    for (size_t i = 0; i < texts.size(); ++i) {
        // ȷ����ɫ
        color textColor = color::WHITE; // Ĭ�ϰ�ɫ
        if (!colorList.empty()) {
            if (i < colorList.size()) {
                textColor = colorList[i];
            }
            else {
                textColor = colorList.back(); // ʹ�����һ����ɫ
            }
        }

        // ������ɫ
        painter.setPen(colorToQColor(textColor));

        // ��������
        QString qText = QString::fromStdString(texts[i]);
        painter.drawText(10, yOffset + fontSize, qText); // ���Ͻ�ƫ����Ϊ (10, yOffset)
        yOffset += fontSize + 5; // �м��
    }

    painter.end();
}

int main() {
    // ����һ��ʾ��ͼ��
    QImage image(600, 400, QImage::Format_RGB32);
    image.fill(Qt::black);

    // Ҫ���Ƶ�����
    std::vector<std::string> texts = {
        "û�ҵ��⾶!",
        "This is a test.",
        "Dynamic font scaling.",
        "Hello, QImage!"
    };

    // ������ɫ�б�
    std::vector<color> colorList = { color::RED, color::GREEN, color::YELLOW, color::CYAN };

    // ���ú�����������
    drawTextOnImage(image, texts, colorList, 0.78);

    // ���������ļ�
    image.save("output.png");

    return 0;
}
