#pragma once

#include <QDialog>
#include "ui_DlgHideScoreSet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgHideScoreSetClass; };
QT_END_NAMESPACE

class DlgHideScoreSet : public QDialog
{
	Q_OBJECT

public:
	DlgHideScoreSet(QWidget *parent = nullptr);
	~DlgHideScoreSet();

private:
	Ui::DlgHideScoreSetClass *ui;
};
