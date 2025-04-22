#include "stdafx.h"
#include "DlgModelManager.h"

DlgModelManager::DlgModelManager(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgModelManagerClass())
{
	ui->setupUi(this);

	build_ui();
	build_connect();
}

DlgModelManager::~DlgModelManager()
{
	delete ui;
}

void DlgModelManager::build_ui()
{
}

void DlgModelManager::build_connect()
{
}
