#include "stdafx.h"
#include "DlgProduceLineSet.h"

#include"NumKeyBord.h"

DlgProduceLineSet::DlgProduceLineSet(QWidget* parent)
	: QDialog(parent)
	, ui(new Ui::DlgProduceLineSetClass())
{
	ui->setupUi(this);

	build_ui();
	build_connect();
}

DlgProduceLineSet::~DlgProduceLineSet()
{
	delete ui;
}

void DlgProduceLineSet::build_ui()
{
}

void DlgProduceLineSet::build_connect()
{
	QObject::connect(ui->pbtn_blowDistance1, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_blowDistance1_clicked);
	QObject::connect(ui->pbtn_blowDistance2, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_blowDistance2_clicked);
	QObject::connect(ui->pbtn_blowDistance3, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_blowDistance3_clicked);
	QObject::connect(ui->pbtn_blowDistance4, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_blowDistance4_clicked);

	QObject::connect(ui->pbtn_blowTime1, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_blowTime1_clicked);
	QObject::connect(ui->pbtn_blowTime2, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_blowTime2_clicked);
	QObject::connect(ui->pbtn_blowTime3, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_blowTime3_clicked);
	QObject::connect(ui->pbtn_blowTime4, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_blowTime4_clicked);

	QObject::connect(ui->pbtn_pixelEquivalent1, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_pixelEquivalent1_clicked);
	QObject::connect(ui->pbtn_pixelEquivalent2, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_pixelEquivalent2_clicked);
	QObject::connect(ui->pbtn_pixelEquivalent3, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_pixelEquivalent3_clicked);
	QObject::connect(ui->pbtn_pixelEquivalent4, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_pixelEquivalent4_clicked);

	QObject::connect(ui->pbtn_limit1, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_limit1_clicked);
	QObject::connect(ui->pbtn_limit2, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_limit2_clicked);
	QObject::connect(ui->pbtn_limit3, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_limit3_clicked);
	QObject::connect(ui->pbtn_limit4, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_limit4_clicked);

	QObject::connect(ui->pbtn_minBrightness, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_minBrightness_clicked);
	QObject::connect(ui->pbtn_maxBrightness, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_maxBrightness_clicked);

	QObject::connect(ui->pbtn_motorSpeed, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_motorSpeed_clicked);
	QObject::connect(ui->pbtn_beltReductionRatio, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_beltReductionRatio_clicked);
	QObject::connect(ui->pbtn_accelerationAndDeceleration, &QPushButton::clicked,
		this, &DlgProduceLineSet::pbtn_accelerationAndDeceleration_clicked);
}

void DlgProduceLineSet::pbtn_blowDistance1_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowDistance1, 2);
	numKeyBoard->exec();
	delete numKeyBoard;
	delete numKeyBoard;
}


void DlgProduceLineSet::pbtn_blowTime1_clicked()
{
	numKeyBoard->exec();

	delete numKeyBoard;

	delete numKeyBoard;
}

void DlgProduceLineSet::pbtn_blowDistance2_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowDistance2, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_blowTime2_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowTime2, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_blowDistance3_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowDistance3, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_blowTime3_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowTime3, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_blowDistance4_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowDistance4, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_blowTime4_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_blowTime4, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_pixelEquivalent1_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_pixelEquivalent1, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_pixelEquivalent2_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_pixelEquivalent2, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_pixelEquivalent3_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_pixelEquivalent3, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_pixelEquivalent4_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_pixelEquivalent4, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_limit1_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_limit1, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_limit2_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_limit2, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_limit3_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_limit3, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_limit4_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_limit4, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_minBrightness_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_minBrightness, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_maxBrightness_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_maxBrightness, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_motorSpeed_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_motorSpeed, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_beltReductionRatio_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_beltReductionRatio, 2);
	numKeyBoard->exec();

}

void DlgProduceLineSet::pbtn_accelerationAndDeceleration_clicked()
{
	auto numKeyBoard = new NumKeyBord(this, ui->pbtn_accelerationAndDeceleration, 2);
	numKeyBoard->exec();

}




