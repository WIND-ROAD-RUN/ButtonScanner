#include "stdafx.h"
#include "PicturesViewer.h"

PicturesViewer::PicturesViewer(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::PicturesViewerClass())
{
	ui->setupUi(this);

	build_ui();
	build_connect();
}

PicturesViewer::~PicturesViewer()
{
	delete ui;
}

void PicturesViewer::build_ui()
{
	_categoryModel = new QStandardItemModel(this);
    ui->treeView_categoryTree->setModel(_categoryModel);

	_picturesListModel = new QStandardItemModel(this);
	ui->listView_picturesList->setModel(_picturesListModel);
}

void PicturesViewer::build_connect()
{
	QObject::connect(ui->pbtn_exit, &QPushButton::clicked,
		this, &PicturesViewer::pbtn_exit_clicked);

    QObject::connect(ui->treeView_categoryTree->selectionModel(), &QItemSelectionModel::selectionChanged,
        this, &PicturesViewer::onCategorySelectionChanged);

}

void PicturesViewer::setRootPath(const QString& path)
{
	_rootPath = path;
}

void PicturesViewer::showEvent(QShowEvent* showEvent)
{
	QMainWindow::showEvent(showEvent);
	updateCategoryList();
}

void PicturesViewer::updateCategoryList()
{
    _categoryModel->clear();
    // 检查 _rootPath 是否有效
    if (_rootPath.isEmpty()) {
        qDebug() << "Root path is empty.";
        return;
    }

    QDir rootDir(_rootPath);
    if (!rootDir.exists()) {
        qDebug() << "Root path does not exist:" << _rootPath;
        return;
    }

    _categoryModel->setHorizontalHeaderLabels({ "文件树" });

    // 遍历 _rootPath 下的所有文件夹
    QStringList categoryFolders = rootDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString& category : categoryFolders) {
        QString categoryPath = rootDir.filePath(category);
        QStandardItem* categoryItem = new QStandardItem(category);

        // 保存绝对路径到节点
        categoryItem->setData(categoryPath, Qt::UserRole);

        // 递归添加子文件夹
        QDir categoryDir(categoryPath);
        addSubFolders(categoryDir, categoryItem);

        _categoryModel->appendRow(categoryItem);
    }

    // 设置模型到 treeView_categoryTree

    ui->treeView_categoryTree->expandAll();

    // 设置当前选中的索引为第一个最深的子节点
    QModelIndex firstDeepestIndex = findFirstDeepestIndex(_categoryModel);
    if (firstDeepestIndex.isValid()) {
        ui->treeView_categoryTree->setCurrentIndex(firstDeepestIndex);
    }

}

QModelIndex PicturesViewer::findFirstDeepestIndex(QStandardItemModel* model)
{
    if (!model || model->rowCount() == 0) {
        return QModelIndex();
    }

    QStandardItem* rootItem = model->invisibleRootItem();
    return findDeepestChild(rootItem);
}

QModelIndex PicturesViewer::findDeepestChild(QStandardItem* parentItem)
{
    if (!parentItem || parentItem->rowCount() == 0) {
        return parentItem ? parentItem->index() : QModelIndex();
    }

    // 遍历子节点，找到第一个最深的子节点
    QStandardItem* firstChild = parentItem->child(0);
    return findDeepestChild(firstChild);
}

void PicturesViewer::addSubFolders(const QDir& parentDir, QStandardItem* parentItem)
{
    // 获取当前目录下的所有子文件夹
    QStringList subFolders = parentDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QString& subFolder : subFolders) {
        QString subFolderPath = parentDir.filePath(subFolder);
        QStandardItem* subFolderItem = new QStandardItem(subFolder);

        // 保存绝对路径到节点
        subFolderItem->setData(subFolderPath, Qt::UserRole);

        // 递归处理子文件夹
        QDir subFolderDir(subFolderPath);
        addSubFolders(subFolderDir, subFolderItem);

        parentItem->appendRow(subFolderItem);
    }
}

void PicturesViewer::pbtn_exit_clicked()
{
	this->hide();
}

void PicturesViewer::onCategorySelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    if (selected.indexes().isEmpty()) {
        qDebug() << "No selection.";
        return;
    }

    QModelIndex currentIndex = selected.indexes().first();

    QString selectedPath = currentIndex.data(Qt::UserRole).toString();

    QDir dir(selectedPath);
    if (!dir.exists()) {
        qDebug() << "Directory does not exist:" << selectedPath;
        return;
    }

    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp" << "*.gif";
    QStringList imageFiles = dir.entryList(filters, QDir::Files | QDir::NoSymLinks);

    updatePicturesList(selectedPath, imageFiles);
}

void PicturesViewer::updatePicturesList(const QString& directoryPath, const QStringList& imageFiles)
{
    _picturesListModel->clear();

    QList<QStandardItem*> items;
    for (const QString& fileName : imageFiles) {
        QString absolutePath = QDir(directoryPath).filePath(fileName);

        QStandardItem* item = new QStandardItem(fileName);

        item->setData(absolutePath, Qt::UserRole);

        items.append(item);
    }

    for (QStandardItem* item : items) {
        _picturesListModel->appendRow(item);
    }
}
