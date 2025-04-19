#pragma once

#include <QDialog>
#include "ui_DlgSelectModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgSelectModelClass; };
QT_END_NAMESPACE

class DlgSelectModel : public QDialog
{
	Q_OBJECT

public:
	DlgSelectModel(QWidget *parent = nullptr);
	~DlgSelectModel();

private:
	Ui::DlgSelectModelClass *ui;
};
