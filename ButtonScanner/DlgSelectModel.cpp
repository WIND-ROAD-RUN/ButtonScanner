#include "stdafx.h"
#include "DlgSelectModel.h"

DlgSelectModel::DlgSelectModel(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgSelectModelClass())
{
	ui->setupUi(this);
}

DlgSelectModel::~DlgSelectModel()
{
	delete ui;
}
