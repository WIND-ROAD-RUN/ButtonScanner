#include "stdafx.h"
#include "DlgModelManager.h"

DlgModelManager::DlgModelManager(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgModelManagerClass())
{
	ui->setupUi(this);
}

DlgModelManager::~DlgModelManager()
{
	delete ui;
}
