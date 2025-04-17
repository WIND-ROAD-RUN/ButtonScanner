#include "stdafx.h"
#include "DlgNewProduction.h"

DlgNewProduction::DlgNewProduction(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgNewProductionClass())
{
	ui->setupUi(this);
	build_ui();
	build_connect();
}

DlgNewProduction::~DlgNewProduction()
{
	delete ui;
}

void DlgNewProduction::build_ui()
{
	//ui->tabWidget->tabBar()->hide();
}

void DlgNewProduction::build_connect()
{
}
