#include "stdafx.h"
#include "ButtonScanner.h"
#include <QtWidgets/QApplication>
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    ButtonScanner w;
    w.show();
    return a.exec();
}