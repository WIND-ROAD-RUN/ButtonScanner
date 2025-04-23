#include "stdafx.h"
#include "DlgHideScoreSet.h"

DlgHideScoreSet::DlgHideScoreSet(QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::DlgHideScoreSetClass())
{
	ui->setupUi(this);

	build_ui();
	build_connect();
}

DlgHideScoreSet::~DlgHideScoreSet()
{
	delete ui;
}

void DlgHideScoreSet::build_ui()
{
}

void DlgHideScoreSet::build_connect()
{
	QObject::connect(ui->pbtn_close, &QPushButton::clicked, this,
		&DlgHideScoreSet::pbtn_close_clicked);
}

void DlgHideScoreSet::pbtn_close_clicked()
{
	this->hide();
}
