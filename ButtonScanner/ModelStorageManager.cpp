#include "stdafx.h"
#include "ModelStorageManager.h"
#include"oso_StorageContext.hpp"
#include"GlobalStruct.h"

ModelStorageManager::ModelStorageManager(QObject *parent)
	: QObject(parent)
{
    build_manager();
    build_tempDirectory();
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

void ModelStorageManager::build_tempDirectory()
{
    auto& RootPath = globalPath.modelStorageManagerTempPath;
    QDir dir(RootPath);
    if (!dir.exists()) {
        if (!dir.mkpath(RootPath)) {
            qWarning() << "Failed to create temporary directory:" << RootPath;
            return;
        }
    }
    QString imageTempDir = RootPath + R"(Image\)";
    QDir dirImage(imageTempDir);
    if (!dirImage.exists()) {
        if (!dirImage.mkpath(imageTempDir)) {
            qWarning() << "Failed to create temporary directory:" << imageTempDir;
            return;
        }
    }
    check_work_temp(imageTempDir);
}

void ModelStorageManager::clear_temp()
{
    QStringList workDirs = { R"(work1\good)", R"(work1\bad)", R"(work2\good)", R"(work2\bad)",
    R"(work3\good)", R"(work3\bad)", R"(work4\good)", R"(work4\bad)" };
    auto& RootPath = globalPath.modelStorageManagerTempPath;
    QString imageTempDir = RootPath + R"(Image\)";

    for (const QString& workDir : workDirs) {
        QString workPath = imageTempDir + workDir + R"(\)";
        QDir workDirObj(workPath);

        if (!workDirObj.exists()) {
            qWarning() << "Directory does not exist:" << workPath;
            continue;
        }

        // 获取所有 PNG 文件
        QStringList pngFiles = workDirObj.entryList(QStringList() << "*.png", QDir::Files);
        for (const QString& file : pngFiles) {
            QString filePath = workPath + file;
            if (!QFile::remove(filePath)) {
                qWarning() << "Failed to delete file:" << filePath;
            }
            else {
                qDebug() << "Deleted file:" << filePath;
            }
        }
    }
	// 清空计数器
    work1_bad_count_ = 0;
	work1_good_count_ = 0;
	work2_bad_count_ = 0;
	work2_good_count_ = 0;
	work3_bad_count_ = 0;
	work3_good_count_ = 0;
	work4_bad_count_ = 0;
	work4_good_count_ = 0;

}

void ModelStorageManager::check_work_temp(const QString& imageRootPath)
{
    check_work1Temp(imageRootPath);
    check_work2Temp(imageRootPath);
    check_work3Temp(imageRootPath);
    check_work4Temp(imageRootPath);
}

void ModelStorageManager::check_work1Temp(const QString& imageRootPath)
{
    QString work1ImageTemp = imageRootPath + R"(work1\)";
    QDir work1Dir(work1ImageTemp);

    if (!work1Dir.exists()) {
        if (!work1Dir.mkpath(work1ImageTemp)) {
            qWarning() << "Failed to create directory:" << work1ImageTemp;
            return;
        }
    }

    QString goodFolder = work1ImageTemp + R"(good\)";
    QString badFolder = work1ImageTemp + R"(bad\)";

    QDir goodDir(goodFolder);
    QDir badDir(badFolder);

    if (!goodDir.exists()) {
        if (!goodDir.mkpath(goodFolder)) {
            qWarning() << "Failed to create directory:" << goodFolder;
            return;
        }
    }

    if (!badDir.exists()) {
        if (!badDir.mkpath(badFolder)) {
            qWarning() << "Failed to create directory:" << badFolder;
            return;
        }
    }

    QStringList goodPngFiles = goodDir.entryList(QStringList() << "*.png", QDir::Files);
    work1_good_count_ = goodPngFiles.size();

    QStringList badPngFiles = badDir.entryList(QStringList() << "*.png", QDir::Files);
    work1_bad_count_ = badPngFiles.size();
}

void ModelStorageManager::check_work2Temp(const QString& imageRootPath)
{
    QString work2ImageTemp = imageRootPath + R"(work2\)";
    QDir work2Dir(work2ImageTemp);

    if (!work2Dir.exists()) {
        if (!work2Dir.mkpath(work2ImageTemp)) {
            qWarning() << "Failed to create directory:" << work2ImageTemp;
            return;
        }
    }

    QString goodFolder = work2ImageTemp + R"(good\)";
    QString badFolder = work2ImageTemp + R"(bad\)";

    QDir goodDir(goodFolder);
    QDir badDir(badFolder);

    if (!goodDir.exists()) {
        if (!goodDir.mkpath(goodFolder)) {
            qWarning() << "Failed to create directory:" << goodFolder;
            return;
        }
    }

    if (!badDir.exists()) {
        if (!badDir.mkpath(badFolder)) {
            qWarning() << "Failed to create directory:" << badFolder;
            return;
        }
    }

    QStringList goodPngFiles = goodDir.entryList(QStringList() << "*.png", QDir::Files);
    work2_good_count_ = goodPngFiles.size();

    QStringList badPngFiles = badDir.entryList(QStringList() << "*.png", QDir::Files);
    work2_bad_count_ = badPngFiles.size();
}

void ModelStorageManager::check_work3Temp(const QString& imageRootPath)
{
    QString work3ImageTemp = imageRootPath + R"(work3\)";
    QDir work3Dir(work3ImageTemp);

    if (!work3Dir.exists()) {
        if (!work3Dir.mkpath(work3ImageTemp)) {
            qWarning() << "Failed to create directory:" << work3ImageTemp;
            return;
        }
    }

    QString goodFolder = work3ImageTemp + R"(good\)";
    QString badFolder = work3ImageTemp + R"(bad\)";

    QDir goodDir(goodFolder);
    QDir badDir(badFolder);

    if (!goodDir.exists()) {
        if (!goodDir.mkpath(goodFolder)) {
            qWarning() << "Failed to create directory:" << goodFolder;
            return;
        }
    }

    if (!badDir.exists()) {
        if (!badDir.mkpath(badFolder)) {
            qWarning() << "Failed to create directory:" << badFolder;
            return;
        }
    }

    QStringList goodPngFiles = goodDir.entryList(QStringList() << "*.png", QDir::Files);
    work3_good_count_ = goodPngFiles.size();

    QStringList badPngFiles = badDir.entryList(QStringList() << "*.png", QDir::Files);
    work3_bad_count_ = badPngFiles.size();
}

void ModelStorageManager::check_work4Temp(const QString& imageRootPath)
{
    QString work4ImageTemp = imageRootPath + R"(work4\)";
    QDir wor41Dir(work4ImageTemp);

    if (!wor41Dir.exists()) {
        if (!wor41Dir.mkpath(work4ImageTemp)) {
            qWarning() << "Failed to create directory:" << work4ImageTemp;
            return;
        }
    }

    QString goodFolder = work4ImageTemp + R"(good\)";
    QString badFolder = work4ImageTemp + R"(bad\)";

    QDir goodDir(goodFolder);
    QDir badDir(badFolder);

    if (!goodDir.exists()) {
        if (!goodDir.mkpath(goodFolder)) {
            qWarning() << "Failed to create directory:" << goodFolder;
            return;
        }
    }

    if (!badDir.exists()) {
        if (!badDir.mkpath(badFolder)) {
            qWarning() << "Failed to create directory:" << badFolder;
            return;
        }
    }

    QStringList goodPngFiles = goodDir.entryList(QStringList() << "*.png", QDir::Files);
    work4_good_count_ = goodPngFiles.size();

    QStringList badPngFiles = badDir.entryList(QStringList() << "*.png", QDir::Files);
    work4_bad_count_ = badPngFiles.size();
}
