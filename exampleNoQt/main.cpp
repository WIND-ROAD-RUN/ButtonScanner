#include <iostream>
#include <thread>
#include <vector>
#include "dsl_PriorityQueue.hpp"

// 插入操作的线程函数
void insertElements(rw::dsl::ThreadSafeDHeap<int, int>& pq, int start, int count) {
    for (int i = 0; i < count; ++i) {
        pq.insert(start + i, start + i); // 插入元素及其优先级
        std::cout << "Inserted: " << (start + i) << " with priority " << (start + i) << std::endl;
    }
}

// 删除操作的线程函数
void removeElements(rw::dsl::ThreadSafeDHeap<int, int>& pq, int start, int count) {
    for (int i = 0; i < count; ++i) {
        try {
            int topElement = pq.top(); // 获取并删除最高优先级的元素
            std::cout << "Removed: " << topElement << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cout << "Remove failed: " << e.what() << std::endl;
        }
    }
}

// 更新操作的线程函数
void updateElements(rw::dsl::ThreadSafeDHeap<int, int>& pq, int start, int count) {
    for (int i = 0; i < count; ++i) {
        pq.update(start + i, start + i + 100); // 更新优先级
        std::cout << "Updated: " << (start + i) << " to new priority " << (start + i + 100) << std::endl;
    }
}

int main() {
    // 创建一个线程安全的优先队列
    rw::dsl::ThreadSafeDHeap<int, int> pq;

    // 创建多个线程
    std::thread t1(insertElements, std::ref(pq), 1, 5);  // 插入 5 个元素
    std::thread t2(insertElements, std::ref(pq), 6, 5);  // 插入另外 5 个元素
    std::thread t3(removeElements, std::ref(pq), 1, 5);  // 删除 5 个元素
    std::thread t4(updateElements, std::ref(pq), 1, 5);  // 更新前 5 个元素的优先级

    // 等待所有线程完成
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // 打印最终队列的大小
    std::cout << "Final size of priority queue: " << pq.size() << std::endl;

    return 0;
}