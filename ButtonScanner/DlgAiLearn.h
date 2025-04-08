#pragma once

#include <QDialog>
#include "ui_DlgAiLearn.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgAiLearnClass; };
QT_END_NAMESPACE

class DlgAiLearn : public QDialog
{
	Q_OBJECT

public:
	DlgAiLearn(QWidget* parent = nullptr);
	~DlgAiLearn();
private:
	void Init();
	void ToStep1();
	void connects();
private:
	Ui::DlgAiLearnClass* ui;
	int moveLen{3000};
		 
	int widget_create_rawX{160};
	int widget_create_rawY{ 120 };
	int widget_check_rawX{580};
	int widget_check_rawY{ 50 };
	int widget_step1_rawX{ 970 };
	int widget_step1_rawY{ 100 };

private slots:
	void pbtn_yes_clicked();
	void pbtn_no_clicked();
	void pbtn_checkColor_clicked();
	void pbtn_checkKnifeShape_clicked();
	void pbtn_close_clicked();



};
