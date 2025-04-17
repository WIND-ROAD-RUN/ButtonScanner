#pragma once

#include <QDialog>
#include "ui_DlgNewProduction.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgNewProductionClass; };
QT_END_NAMESPACE

class DlgNewProduction : public QDialog
{
	Q_OBJECT

public:
	DlgNewProduction(QWidget *parent = nullptr);
	~DlgNewProduction();
private:
	void build_ui();
	void build_connect();

private:
	Ui::DlgNewProductionClass *ui;
};
