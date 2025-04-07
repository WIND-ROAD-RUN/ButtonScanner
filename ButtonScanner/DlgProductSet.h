#pragma once

#include <QDialog>
#include "ui_DlgProductSet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgProductSetClass; };
QT_END_NAMESPACE

class DlgProductSet : public QDialog
{
	Q_OBJECT

public:
	DlgProductSet(QWidget* parent = nullptr);
	~DlgProductSet();

private:
	void build_ui();
	void read_config();
	void read_image();
	void build_radioButton();
	void build_connect();
private:
	Ui::DlgProductSetClass* ui;
private slots:
	void pbtn_outsideDiameterValue_clicked();
	void pbtn_outsideDiameterDeviation_clicked();
	void pbtn_photography_clicked();
	void pbtn_blowTime_clicked();
	void rbtn_edgeDamageSimilarity_clicked();
	void pbtn_outerRadius_clicked();
	void pbtn_innerRadius_clicked();
	void ptn_holesCountValue_clicked();
	void pbtn_brokenEyeSimilarity_clicked();
	void pbtn_crackSimilarity_clicked();
	void pbtn_apertureValue_clicked();
	void pbtn_apertureSimilarity_clicked();
	void pbtn_holeCenterDistanceValue_clicked();
	void pbtn_holeCenterDistanceSimilarity_clicked();
	void pbtn_specifyColorDifferenceR_clicked();
	void pbtn_specifyColorDifferenceG_clicked();
	void pbtn_specifyColorDifferenceB_clicked();
	void pbtn_specifyColorDifferenceDeviation_clicked();
	void pbtn_largeColorDifferenceDeviation_clicked();
};
