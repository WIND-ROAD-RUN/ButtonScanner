#include <QImage>
#include <QString>
#include <QDir>
#include <QMutex>
#include <QThread>
#include <QQueue>
#include <QWaitCondition>
#include <QDateTime>
#include <atomic>
#include <iostream>
#include <vector>

class ImageSaveEngine : public QThread {
    Q_OBJECT

public:
    ImageSaveEngine(QObject* parent = nullptr, int threadCount = 4)
        : QThread(parent), stopFlag(false), threadCount(threadCount) {
    }

    ~ImageSaveEngine() {
        stop();
    }

    // 设置根路径
    void setRootPath(const QString& rootPath) {
        QMutexLocker locker(&mutex);
        this->rootPath = rootPath;
        QDir dir(rootPath);
        if (!dir.exists()) {
            dir.mkpath(".");
        }
    }

    // 修改后的 pushImage 方法
    void pushImage(const QImage& image, const QString& classify, const QString& namePrefix) {
        QMutexLocker locker(&mutex);
        if (saveQueue.size() >= maxQueueSize) {
            std::cerr << "Queue is full, dropping image." << std::endl;
            return;
        }
        saveQueue.enqueue({ image, classify });
        condition.wakeOne();
    }

    // 停止线程
    void stop() {
        {
            QMutexLocker locker(&mutex);
            stopFlag = true;
            condition.wakeAll();
        }
        for (auto& thread : workerThreads) {
            thread->wait();
            delete thread;
        }
        workerThreads.clear();
    }

    // 启动线程池
    void startEngine() {
        for (int i = 0; i < threadCount; ++i) {
            QThread* worker = QThread::create([this]() { this->processImages(); });
            workerThreads.push_back(worker);
            worker->start();
        }
    }

protected:
    void processImages() {
        while (true) {
            QList<QPair<QImage, QString>> tasks;

            {
                QMutexLocker locker(&mutex);
                if (saveQueue.isEmpty() && !stopFlag) {
                    condition.wait(&mutex);
                }

                if (stopFlag && saveQueue.isEmpty()) {
                    break;
                }

                // 批量取出任务
                while (!saveQueue.isEmpty() && tasks.size() < batchSize) {
                    tasks.append(saveQueue.dequeue());
                }
            }

            // 保存图片
            for (const auto& task : tasks) {
                saveImage(task.first, task.second);
            }
        }
    }

private:
    // 修改后的 saveImage 方法
    void saveImage(const QImage& image, const QString& classifyWithPrefix) {
        QDir dir(rootPath + "/" + classifyWithPrefix);
        if (!dir.exists()) {
            dir.mkpath(".");
        }

        // 获取当前时间
        QDateTime currentTime = QDateTime::currentDateTime();
        QString timestamp = currentTime.toString("yyyyMMddhhmmsszzz"); // 年月日时分秒毫秒

        // 构造文件名
        QString fileName = dir.filePath(classifyWithPrefix + timestamp + ".png");

        // 保存图片
        if (!image.save(fileName)) {
            std::cerr << "Failed to save image: " << fileName.toStdString() << std::endl;
        }
    }

    QString rootPath;
    QQueue<QPair<QImage, QString>> saveQueue;
    QMutex mutex;
    QWaitCondition condition;
    std::atomic<bool> stopFlag;

    const int maxQueueSize = 500; // 队列最大容量
    const int batchSize = 20;     // 每次批量保存的图片数量
    int threadCount;              // 消费者线程数量
    std::vector<QThread*> workerThreads;
};