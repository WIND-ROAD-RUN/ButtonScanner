#include"stdafx.h"

#include "NumKeyBord.h"


NumKeyBord::NumKeyBord(QWidget* parent, QPushButton* button, int _type)
	: QDialog(parent),
	inputLineEdit(new QLineEdit(this)),
	keyboardWidget(new QWidget(this))
{
	btn = button;
	type = _type;

	// 设置主窗口的中央部件
	QWidget* centralWidget = new QWidget(this);
	NumKeyBord::setWindowTitle("");
	// 创建主布局
	QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    this->setLayout(mainLayout);

	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

	// 设置输入框
	inputLineEdit->setReadOnly(true); // 设置为只读，避免直接输入
	inputLineEdit->setFixedHeight(40);
	mainLayout->addWidget(inputLineEdit);

	// 创建数字键盘布局
	QGridLayout* keyboardLayout = new QGridLayout();
	QStringList keys;

	keys = { "1", "2", "3",
			"4", "5", "6",
			"7", "8", "9",
			"-", "0", ".",
			"Delete", "Enter", "Close" };

	int pos = 0;
	int totalRows = (keys.size() + 2) / 3; // 每行3个按钮
	for (int i = 0; i < totalRows; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (pos >= keys.size())
				break;
			QPushButton* button = new QPushButton(keys[pos], this);
			button->setFixedSize(100, 50);
			keyboardLayout->addWidget(button, i, j);
			if (keys[pos] == "Close")
			{// 连接 "Close" 按钮到关闭槽
				connect(button, &QPushButton::clicked, this, &NumKeyBord::closeKeyboard);
				button->setStyleSheet("QPushButton {"
					"background-color: #ff4d4d;" // 红色背景
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
				// 设置其他按钮的样式
				if (keys[pos] == "-" || keys[pos] == ".") {
					// 特殊按钮样式（仅在 Decimal 模式下）
					button->setStyleSheet("QPushButton {"
						"font-size: 18px;"
						"background-color: #d9d9d9;" // 灰色背景
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

	// 添加键盘布局到主布局
	keyboardWidget->setLayout(keyboardLayout);
	mainLayout->addWidget(keyboardWidget);
	// 设置窗口大小，根据输入类型调整高度
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
	this->close(); // 关闭当前窗口
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
			currentText.chop(1); // 删除最后一个字符
			inputLineEdit->setText(currentText);
		}
	}
	else if (key == "Enter") {
		// 在这里处理确认操作，比如提交输入内容
		// 示例：弹出一个消息框显示输入内容
		QString input = inputLineEdit->text();
		btn->setText(input);
		emit closed();


		this->close();
	}
	else if (key == ".") {
		if (type == 1)
			return;

		QString currentText = inputLineEdit->text();
		// 检查是否已经存在小数点
		if (type == 2 && !currentText.contains('.')) {
			if (currentText.isEmpty()) {
				// 如果输入为空，前置一个零
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
				// 如果已经有负号，则去掉
				inputLineEdit->setText(currentText.mid(1));
			}
			else {
				// 添加负号
				inputLineEdit->setText("-" + currentText);
			}
		else
			inputLineEdit->setText(currentText + "-");
	}
	else  {
		// 在 Character 模式下允许输入字符
		inputLineEdit->setText(inputLineEdit->text() + key);
	}
}