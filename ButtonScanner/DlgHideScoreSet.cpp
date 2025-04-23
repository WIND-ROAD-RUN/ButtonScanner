#include "stdafx.h"
#include "DlgHideScoreSet.h"

#include "GlobalStruct.h"
#include "NumKeyBord.h"

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
	QObject::connect(ui->pbtn_outsideDiameterScore, &QPushButton::clicked, this,
		&DlgHideScoreSet::pbtn_outsideDiameterScore_clicked);
	QObject::connect(ui->pbtn_forAndAgainstScore, &QPushButton::clicked, this,
		&DlgHideScoreSet::pbtn_forAndAgainstScore_clicked);
}

void DlgHideScoreSet::pbtn_close_clicked()
{
	this->hide();
}

void DlgHideScoreSet::pbtn_outsideDiameterScore_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_outsideDiameterScore, 2);
	numKeyBoard->exec();

	auto& GlobalStructData = GlobalStructData::getInstance();
	GlobalStructData.dlgHideScoreSetConfig.outsideDiameterScore = ui->pbtn_outsideDiameterScore->text().toDouble();

	delete numKeyBoard;
}

void DlgHideScoreSet::pbtn_forAndAgainstScore_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_forAndAgainstScore, 2);
	numKeyBoard->exec();
	auto& GlobalStructData = GlobalStructData::getInstance();
	GlobalStructData.dlgHideScoreSetConfig.forAndAgainstScore = ui->pbtn_forAndAgainstScore->text().toDouble();
	delete numKeyBoard;
}
