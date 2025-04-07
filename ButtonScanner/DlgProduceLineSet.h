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
	DlgProduceLineSet(QWidget* parent = nullptr);
	~DlgProduceLineSet();
 
private:
    void build_ui();

    void build_connect();

private:
    Ui::DlgProduceLineSetClass* ui;
public:
    void pbtn_blowDistance1_clicked();
};
