#include "WarningInfoList.h"

#include "ui_WarningInfoList.h"

WarningInfoList::WarningInfoList(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::WarningInfoListClass())
{
	ui->setupUi(this);
}

WarningInfoList::~WarningInfoList()
{
	delete ui;
}
