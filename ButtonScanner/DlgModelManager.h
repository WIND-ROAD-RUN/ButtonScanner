#pragma once

#include <QDialog>

#include "cdm_AiModelConfig.h"
#include"cdm_AiModelConfigIndex.h"
#include "ui_DlgModelManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DlgModelManagerClass; };
QT_END_NAMESPACE

class DlgModelManager : public QDialog
{
	Q_OBJECT

public:
	DlgModelManager(QWidget *parent = nullptr);
	~DlgModelManager();
private:
	QStringListModel* _ModelListModel;
	QStandardItemModel* _ModelInfoModel;
	rw::cdm::AiModelConfigIndex _configIndex;
private:
	void build_ui();
	void build_connect();

private:
	Ui::DlgModelManagerClass *ui;

private slots:
	void pbtn_exit_clicked();

protected:
	void showEvent(QShowEvent*) override;
private:
	QString formatDateString(const std::string& dateStr);
	
private:
	QString findXmlFile(const QString& rootPath);
    
private:
	void flashModelList();
	void falshModelInfoTabel();

};
