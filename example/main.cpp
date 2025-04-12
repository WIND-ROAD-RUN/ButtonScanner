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

// 定义颜色枚举
int main() {
    ImageSaveEngine engine(nullptr, 4); // 使用 4 个消费者线程
    engine.setRootPath("D:/Images");

    engine.startEngine();

    QImage image(100, 100, QImage::Format_RGB32);
    image.fill(Qt::red);

    for (int i = 0; i < 2400; ++i) {
        engine.pushImage(image, "Category1", "NG");
    }

    QThread::sleep(5); // 模拟其他操作

    engine.stop();
    return 0;
}