#include"stdafx.h"

#include "NumKeyBord.h"


NumKeyBord::NumKeyBord(QWidget* parent, QPushButton* button, int _type)
	: QDialog(parent),
	inputLineEdit(new QLineEdit(this)),
	keyboardWidget(new QWidget(this))
{
	btn = button;
	type = _type;

	// ���������ڵ����벿��
	QWidget* centralWidget = new QWidget(this);
	NumKeyBord::setWindowTitle("");
	// ����������
	QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    this->setLayout(mainLayout);

	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

	// ���������
	inputLineEdit->setReadOnly(true); // ����Ϊֻ��������ֱ������
	inputLineEdit->setFixedHeight(40);
	mainLayout->addWidget(inputLineEdit);

	// �������ּ��̲���
	QGridLayout* keyboardLayout = new QGridLayout();
	QStringList keys;

	keys = { "1", "2", "3",
			"4", "5", "6",
			"7", "8", "9",
			"-", "0", ".",
			"Delete", "Enter", "Close" };

	int pos = 0;
	int totalRows = (keys.size() + 2) / 3; // ÿ��3����ť
	for (int i = 0; i < totalRows; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (pos >= keys.size())
				break;
			QPushButton* button = new QPushButton(keys[pos], this);
			button->setFixedSize(100, 50);
			keyboardLayout->addWidget(button, i, j);
			if (keys[pos] == "Close")
			{// ���� "Close" ��ť���رղ�
				connect(button, &QPushButton::clicked, this, &NumKeyBord::closeKeyboard);
				button->setStyleSheet("QPushButton {"
					"background-color: #ff4d4d;" // ��ɫ����
					"color: white;"
					"font-size: 16px;"
					"border: none;"
					"border-radius: 5px;"
					"}"
					"QPushButton:pressed {"
					"background-color: #ff1a1a;"
					"}");
			}
			else
			{
				connect(button, &QPushButton::clicked, this, &NumKeyBord::handleButton);
				// ����������ť����ʽ
				if (keys[pos] == "-" || keys[pos] == ".") {
					// ���ⰴť��ʽ������ Decimal ģʽ�£�
					button->setStyleSheet("QPushButton {"
						"font-size: 18px;"
						"background-color: #d9d9d9;" // ��ɫ����
						"border: 1px solid #aaa;"
						"border-radius: 5px;"
						"}"
						"QPushButton:pressed {"
						"background-color: #bfbfbf;"
						"}");
				}
				else {
					button->setStyleSheet("QPushButton {"
						"font-size: 18px;"
						"background-color: #f0f0f0;"
						"border: 1px solid #ccc;"
						"border-radius: 5px;"
						"}"
						"QPushButton:pressed {"
						"background-color: #d0d0d0;"
						"}");
				}
			}
			pos++;
		}
	}

	// ��Ӽ��̲��ֵ�������
	keyboardWidget->setLayout(keyboardLayout);
	mainLayout->addWidget(keyboardWidget);
	// ���ô��ڴ�С�������������͵����߶�
		setFixedSize(350, 400);  
	 
	 
}

NumKeyBord::~NumKeyBord()
{

}

void NumKeyBord::handleSpace()
{
	if (type == 0 || type > 2) {
		inputLineEdit->setText(inputLineEdit->text() + " ");
	}
}
void NumKeyBord::closeKeyboard()
{
	this->close(); // �رյ�ǰ����
}
void NumKeyBord::handleButton()
{
	QPushButton* button = qobject_cast<QPushButton*>(sender());
	if (!button)
		return;

	QString key = button->text();

	if (key == "Delete") {
		QString currentText = inputLineEdit->text();
		if (!currentText.isEmpty()) {
			currentText.chop(1); // ɾ�����һ���ַ�
			inputLineEdit->setText(currentText);
		}
	}
	else if (key == "Enter") {
		// �����ﴦ��ȷ�ϲ����������ύ��������
		// ʾ��������һ����Ϣ����ʾ��������
		QString input = inputLineEdit->text();
		btn->setText(input);
		emit closed();


		this->close();
	}
	else if (key == ".") {
		if (type == 1)
			return;

		QString currentText = inputLineEdit->text();
		// ����Ƿ��Ѿ�����С����
		if (type == 2 && !currentText.contains('.')) {
			if (currentText.isEmpty()) {
				// �������Ϊ�գ�ǰ��һ����
				inputLineEdit->setText("0.");
			}
			else {
				inputLineEdit->setText(currentText + ".");
			}
		}
		else {
			inputLineEdit->setText(currentText + ".");
		}
	}
	else if (key == "-") {
		QString currentText = inputLineEdit->text();
		if (type == 1 || type == 2)
			if (currentText.startsWith("-")) {
				// ����Ѿ��и��ţ���ȥ��
				inputLineEdit->setText(currentText.mid(1));
			}
			else {
				// ��Ӹ���
				inputLineEdit->setText("-" + currentText);
			}
		else
			inputLineEdit->setText(currentText + "-");
	}
	else  {
		// �� Character ģʽ�����������ַ�
		inputLineEdit->setText(inputLineEdit->text() + key);
	}
}