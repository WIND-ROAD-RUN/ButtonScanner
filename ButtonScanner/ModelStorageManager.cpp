#include "stdafx.h"
#include "ModelStorageManager.h"
#include"oso_StorageContext.hpp"
#include"GlobalStruct.h"

ModelStorageManager::ModelStorageManager(QObject *parent)
	: QObject(parent)
{
    build_manager();

}

ModelStorageManager::~ModelStorageManager()
{
    destroy_manager();
}

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

void ModelStorageManager::build_manager()
{
    auto& RootPath = globalPath.modelStorageManagerRootPath;
    auto& globalStruct = GlobalStructData::getInstance();
    QString configPath = RootPath + R"(modelStorageIndex.xml)";

    if (!QFile::exists(configPath)) {
        globalStruct.storeContext->save(_config_index, configPath.toStdString());
    }
    else {
		_config_index = *(globalStruct.storeContext->load(configPath.toStdString()));
    }
}

void ModelStorageManager::destroy_manager()
{
    auto& RootPath = globalPath.modelStorageManagerRootPath;
    auto& globalStruct = GlobalStructData::getInstance();
    QString configPath = RootPath + R"(modelStorageIndex.xml)";
    globalStruct.storeContext->save(_config_index, configPath.toStdString());
}
