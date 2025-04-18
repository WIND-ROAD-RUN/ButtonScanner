#include "stdafx.h"
#include "ModelStorageManager.h"

ModelStorageManager::ModelStorageManager(QObject *parent)
	: QObject(parent)
{}

ModelStorageManager::~ModelStorageManager()
{}

void ModelStorageManager::setRootPath(QString path)
{
    QDir dir(path);
    if (!dir.exists()) {
        if (!dir.mkpath(path)) {
            qWarning() << "Failed to create directory:" << path;
            return;
        }
    }
    _rootPath = path;
}
QString ModelStorageManager::getRootPath()
{
	return _rootPath;
}