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
#include"QApplication"

void drawTextOnImage(QImage& image, const QVector<QString>& texts, const QVector<QColor>& colorList, double proportion) {
	if (texts.isEmpty() || proportion <= 0.0 || proportion > 1.0) {
		return; // 无效输入直接返回
	}

	QPainter painter(&image);
	painter.setRenderHint(QPainter::Antialiasing);

	// 计算字体大小
	int imageHeight = image.height();
	int totalTextHeight = static_cast<int>(imageHeight * proportion);
	int fontSize = totalTextHeight / texts.size();

	QFont font = painter.font();
	font.setPixelSize(fontSize);
	painter.setFont(font);

	// 起始位置
	int x = 0;
	int y = 0;

	// 绘制每一行文字
	for (int i = 0; i < texts.size(); ++i) {
		// 获取颜色
		QColor color = (i < colorList.size()) ? colorList[i] : colorList.last();
		painter.setPen(color);

		// 绘制文字
		painter.drawText(x, y + fontSize, texts[i]);

		// 更新 y 坐标
		y += fontSize;
	}

	painter.end();
}

// 定义颜色枚举
int main(int argc, char** argv) {
	QApplication app(argc, argv);
	// 从给定路径加载图片
	QString imagePath = R"(C:\Users\rw\Desktop\demo.png)"; // 替换为实际路径
	QImage image(imagePath);

	// 检查图片是否加载成功
	if (image.isNull()) {
		qWarning("Failed to load image from path: %s", qPrintable(imagePath));
		return -1;
	}

	QVector<QString> texts = { "Hello", "World", "Qt" ,"Qt" ,"Qt" ,"Qt" ,"Qt" };
	QVector<QColor> colors = { Qt::red, Qt::green, Qt::blue };
	double proportion = 0.6;

	drawTextOnImage(image, texts, colors, proportion);

	// 保存结果
	image.save("output.png");
	return 0;
}