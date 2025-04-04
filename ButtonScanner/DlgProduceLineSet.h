#pragma once

#include <QDialog>
#include "ui_DlgProduceLineSet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgProduceLineSetClass; };
QT_END_NAMESPACE

class DlgProduceLineSet : public QDialog
{
    Q_OBJECT

public:
    DlgProduceLineSet(QWidget *parent = nullptr);
    ~DlgProduceLineSet();

private:
    Ui::DlgProduceLineSetClass *ui;
};
