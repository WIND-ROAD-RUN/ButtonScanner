#include "stdafx.h"
#include "DlgHideScoreSet.h"

DlgHideScoreSet::DlgHideScoreSet(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgHideScoreSetClass())
{
	ui->setupUi(this);
}

DlgHideScoreSet::~DlgHideScoreSet()
{
	delete ui;
}
