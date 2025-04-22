#pragma once

#include <QMainWindow>
#include "ui_PicturesViewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PicturesViewerClass; };
QT_END_NAMESPACE

class PicturesViewer : public QMainWindow
{
	Q_OBJECT

public:
	PicturesViewer(QWidget* parent = nullptr);
	~PicturesViewer();

private:
	Ui::PicturesViewerClass* ui;
};
