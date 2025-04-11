#pragma once

#include<memory>

#include"ImageProcessorModule.h"

#include"scc_Motion.h"
#include"ime_ModelEngine.h"
#include"rqw_CameraObjectThread.hpp"
#include"cdm_ButtonScannerMainWindow.h"
#include"cdm_ButtonScannerDlgProductSet.h"
#include"oso_StorageContext.hpp"
#include<QString>
#include <cdm_ButtonScannerProduceLineSet.h>


template<typename T>
class ConcurrentQueue {
private:
    struct Node {
        std::shared_ptr<T> data;
        std::unique_ptr<Node> next;
        Node() : data(nullptr) {}
        explicit Node(T value) : data(std::make_shared<T>(std::move(value))) {}
    };

    std::unique_ptr<Node> head;  // 虚拟头节点，head->next为第一个实际节点
    Node* tail;                  // 尾节点指针
    std::mutex head_mutex;       // 保护头节点操作
    std::mutex tail_mutex;       // 保护尾节点操作

public:
    ConcurrentQueue() : head(std::make_unique<Node>()), tail(head.get()) {}

    // 禁止拷贝和移动
    ConcurrentQueue(const ConcurrentQueue&) = delete;
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;

    void enqueue(T value) {
        // 创建新节点并准备数据
        auto new_node = std::make_unique<Node>(std::move(value));
        Node* new_tail = new_node.get();

        // 锁住尾节点进行操作
        std::lock_guard<std::mutex> lock(tail_mutex);
        tail->next = std::move(new_node);  // 将新节点链接到队列尾部
        tail = new_tail;                   // 更新尾节点指针
    }

    std::shared_ptr<T> dequeue() {
        std::lock_guard<std::mutex> lock(head_mutex);

        // 检查队列是否为空
        if (!head->next) {
            return nullptr;
        }

        // 取出数据并更新头节点
        std::unique_ptr<Node> old_head = std::move(head);
        head = std::move(old_head->next);  // head现在指向原第一个实际节点
        return head->data;                 // 返回数据（shared_ptr保证生命周期）
    }

    bool empty() {
        // 检查队列是否为空需要同时锁住头尾，避免竞争
        std::lock_guard<std::mutex> head_lock(head_mutex);
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return head.get() == tail;
    }
};

namespace zwy {
    namespace scc {
        class Motion;
    }
}

class GlobalStruct
    :public QObject
{
    Q_OBJECT
public:
    ConcurrentQueue<float> LocationQueue;
public:
    void buildConfigManager(rw::oso::StorageType type);
public:
    void ReadConfig();
    void ReadMainWindowConfig();
    void ReadDlgProduceLineSetConfig();
    void ReadDlgProductSetConfig();
public:
    void saveConfig();
    void saveMainWindowConfig();
    void saveDlgProduceLineSetConfig();
    void saveDlgProductSetConfig();
    std::unique_ptr<rw::oso::StorageContext> _StoreContext{ nullptr };
public:
    QString mainwindowFilePath;
	QString dlgProduceLineSetFilePath;
    QString dlgProductSetFilePath;
    rw::cdm::ButtonScannerMainWindow mainWindowConfig{};
	rw::cdm::ButtonScannerProduceLineSet dlgProduceLineSetConfig{};
    rw::cdm::ButtonScannerDlgProductSet dlgProductSetConfig{};
public:
    QString cameraIp1{ "11" };
    QString cameraIp2{ "12" };
    QString cameraIp3{ "13" };
    QString cameraIp4{ "14" };
public:
    QString enginePath{ R"(C:\Users\34615\Desktop\best.engine)" };
    QString namePath{ R"(C:\Users\34615\Desktop\index.names)" };
public:

    void buildCamera();
    void startMonitor();
    void destroyCamera();
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera1{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera2{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera3{ nullptr };
    std::unique_ptr<rw::rqw::CameraPassiveThread> _camera4{ nullptr };

public:
    //调用前确保模型文件存在且以设置
    void buildImageProcessingModule(size_t num);
    void destroyImageProcessingModule();

    std::unique_ptr<ImageProcessingModule> _imageProcessingModule1{ nullptr };
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule2{ nullptr };
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule3{ nullptr };
    std::unique_ptr<ImageProcessingModule> _imageProcessingModule4{ nullptr };


public:
    static GlobalStruct& getInstance()
    {
        static GlobalStruct instance;
        return instance;
    }

    GlobalStruct(const GlobalStruct&) = delete;
    GlobalStruct& operator=(const GlobalStruct&) = delete;
private:
    GlobalStruct();
    ~GlobalStruct() = default;
};