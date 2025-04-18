#pragma once

#include <QObject>

#include"cdm_AiModelConfigIndex.h"

class ModelStorageManager  : public QObject
{
	Q_OBJECT
private:
	rw::cdm::AiModelConfigIndex _config_index{};
public:
	ModelStorageManager(QObject *parent);
	~ModelStorageManager();
public:
	void setRootPath(QString path);
	QString getRootPath();
private:
	void build_manager();
	void destroy_manager();
private:
	QString _rootPath;
};
