#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ButtonScanner.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ButtonScannerClass; };
QT_END_NAMESPACE

class ButtonScanner : public QMainWindow
{
    Q_OBJECT

public:
    ButtonScanner(QWidget *parent = nullptr);
    ~ButtonScanner();

private:
    void set_radioButton();

private:
    void build_ui();
    void build_connect();

private:
    Ui::ButtonScannerClass *ui;

private slots:
    void pbtn_exit_clicked();
    void pbtn_set_clicked();
    void pbtn_newProduction_clicked();
};
