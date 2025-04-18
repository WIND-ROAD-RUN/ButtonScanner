#include "example.h"

example::example(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::exampleClass())
{
	ui->setupUi(this);
}

example::~example()
{
	delete ui;
}