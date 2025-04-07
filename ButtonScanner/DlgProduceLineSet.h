#pragma once

#include <QDialog>
#include "ui_DlgProduceLineSet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgProduceLineSetClass; };
QT_END_NAMESPACE

class DlgProduceLineSet : public QDialog
{
	Q_OBJECT

public:
	DlgProduceLineSet(QWidget* parent = nullptr);
	~DlgProduceLineSet();

private:
	void build_ui();
	void read_config();

	void build_connect();

private:
	Ui::DlgProduceLineSetClass* ui;

private slots:
	void  pbtn_blowDistance1_clicked();
	void  pbtn_blowDistance2_clicked();
	void  pbtn_blowDistance3_clicked();
	void  pbtn_blowDistance4_clicked();

	void pbtn_blowTime1_clicked();
	void pbtn_blowTime2_clicked();
	void pbtn_blowTime3_clicked();
	void pbtn_blowTime4_clicked();

	void pbtn_pixelEquivalent1_clicked();
	void pbtn_pixelEquivalent2_clicked();
	void pbtn_pixelEquivalent3_clicked();
	void pbtn_pixelEquivalent4_clicked();

	void pbtn_limit1_clicked();
	void pbtn_limit2_clicked();
	void pbtn_limit3_clicked();
	void pbtn_limit4_clicked();

	void pbtn_minBrightness_clicked();
	void pbtn_maxBrightness_clicked();

	void pbtn_motorSpeed_clicked();
	void pbtn_beltReductionRatio_clicked();
	void pbtn_accelerationAndDeceleration_clicked();
};
