#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class WarningInfoListClass; };
QT_END_NAMESPACE

class WarningInfoList : public QDialog
{
	Q_OBJECT

public:
	WarningInfoList(QWidget *parent = nullptr);
	~WarningInfoList();

private:
	Ui::WarningInfoListClass *ui;
};
