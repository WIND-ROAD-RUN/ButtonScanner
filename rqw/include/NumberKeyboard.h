#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class NumberKeyboardClass; };
QT_END_NAMESPACE

class NumberKeyboard : public QDialog
{
	Q_OBJECT
private:
	QString value;
public:
	NumberKeyboard(QWidget *parent = nullptr);
	~NumberKeyboard();
public:
	QString getValue() const { return value; }
private:
	void build_ui();
	void build_connect();
protected:
	void showEvent(QShowEvent*) override;

private:
	Ui::NumberKeyboardClass *ui;
private slots:
	void pbtn_num1_clicked();
	void pbtn_num2_clicked();
	void pbtn_num3_clicked();
	void pbtn_num4_clicked();
	void pbtn_num5_clicked();
	void pbtn_num6_clicked();
	void pbtn_num7_clicked();
	void pbtn_num8_clicked();
	void pbtn_num9_clicked();
	void pbtn_num0_clicked();
	void pbtn_bar_clicked();
	void pbtn_point_clicked();
	void pbtn_delete_clicked();
	void pbtn_cancel_clicked();
	void pbtn_ok_clicked();
};
