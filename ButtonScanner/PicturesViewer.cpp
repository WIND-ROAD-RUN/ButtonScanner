#include "stdafx.h"
#include "PicturesViewer.h"

PicturesViewer::PicturesViewer(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::PicturesViewerClass())
{
	ui->setupUi(this);
}

PicturesViewer::~PicturesViewer()
{
	delete ui;
}
