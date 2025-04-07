#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

class QPushButton;

class NumKeyBord : public QMainWindow
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
	void show();

private slots:
	void handleButton();
	void handleSpace();
	void closeKeyboard();   // ����رհ�ť���

signals:
	void closed();  // �Զ���ر��ź�

private:
	QLineEdit* inputLineEdit;
	QWidget* keyboardWidget;
	QPushButton* btn;
	int type;

};

#endif // MAINWINDOW_H#pragma once
