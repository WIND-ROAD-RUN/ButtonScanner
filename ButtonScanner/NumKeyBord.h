#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

class QPushButton;

class NumKeyBord
	: public QDialog
{
	Q_OBJECT

public:
	/// <summary>
	///
	/// </summary>
	/// <param name="parent"></param>
	/// <param name="type">0:string,1:int,2:double</param>
	NumKeyBord(QWidget* parent = nullptr, QPushButton* button = nullptr, int _type = 0);
	~NumKeyBord();

private slots:
	void handleButton();
	void handleSpace();
	void closeKeyboard();   // 处理关闭按钮点击

signals:
	void closed();  // 自定义关闭信号

private:
	QLineEdit* inputLineEdit;
	QWidget* keyboardWidget;
	QPushButton* btn;
	int type;
};

#endif // MAINWINDOW_H#pragma once
