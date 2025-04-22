#pragma once

#include <QMainWindow>
#include "ui_PicturesViewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PicturesViewerClass; };
QT_END_NAMESPACE

class PicturesViewer : public QMainWindow
{
	Q_OBJECT
private:
	QString _rootPath;
private:
	QStandardItemModel* _categoryModel;
	QStandardItemModel* _picturesListModel;

public:
	PicturesViewer(QWidget* parent = nullptr);
	~PicturesViewer();

private:
	void build_ui();
	void build_connect();

public:
	void setRootPath(const QString & path);
protected:
	void showEvent(QShowEvent*) override;
private:
	void updateCategoryList();
	void addSubFolders(const QDir& parentDir, QStandardItem* parentItem);
	QModelIndex findFirstDeepestIndex(QStandardItemModel* model);
	QModelIndex findDeepestChild(QStandardItem* parentItem);
	void updatePicturesList(const QString& directoryPath, const QStringList& imageFiles);
private:
	Ui::PicturesViewerClass* ui;

private slots:
	void pbtn_exit_clicked();
	void onCategorySelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
	

};
