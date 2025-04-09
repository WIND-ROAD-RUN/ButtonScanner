#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_example.h"

QT_BEGIN_NAMESPACE
namespace Ui { class exampleClass; };
QT_END_NAMESPACE

class example : public QMainWindow
{
    Q_OBJECT

public:
    example(QWidget* parent = nullptr);
    ~example();

private:
    Ui::exampleClass* ui;
};
