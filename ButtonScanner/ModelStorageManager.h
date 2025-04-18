#pragma once

#include <QObject>

class ModelStorageManager  : public QObject
{
	Q_OBJECT

public:
	ModelStorageManager(QObject *parent);
	~ModelStorageManager();
};
