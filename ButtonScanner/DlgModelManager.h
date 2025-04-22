#pragma once

#include <QDialog>
#include "ui_DlgModelManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgModelManagerClass; };
QT_END_NAMESPACE

class DlgModelManager : public QDialog
{
	Q_OBJECT

public:
	DlgModelManager(QWidget *parent = nullptr);
	~DlgModelManager();

private:
	Ui::DlgModelManagerClass *ui;
};
