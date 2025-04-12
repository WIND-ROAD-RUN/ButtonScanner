#pragma once
#include <queue>
#include <shared_mutex>
#include <vector>
#include <functional>
#include <optional>

class ThreadSafeMinHeap {
public:
    // 构造函数，允许预设容量
    explicit ThreadSafeMinHeap(size_t initialCapacity = 50) {
        // 使用临时容器预分配容量
        reserveCapacity(minHeap1_, initialCapacity);
        reserveCapacity(minHeap2_, initialCapacity);
    }

    // 插入元素
    void push(float value) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        // 分片插入：根据当前计数选择堆
        if (insertCount_ % 2 == 0) {
            minHeap1_.push(value);
        }
        else {
            minHeap2_.push(value);
        }
        ++insertCount_;
    }

    // 获取最小值（无锁读取）
    bool tryGetMin(float& minValue) {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        if (minHeap1_.empty() && minHeap2_.empty()) {
            return false; // 两个堆都为空
        }

        // 获取两个堆的最小值
        std::optional<float> min1 = minHeap1_.empty() ? std::nullopt : std::optional<float>(minHeap1_.top());
        std::optional<float> min2 = minHeap2_.empty() ? std::nullopt : std::optional<float>(minHeap2_.top());

        // 比较两个堆的最小值
        if (min1 && min2) {
            minValue = std::min(*min1, *min2);
        }
        else if (min1) {
            minValue = *min1;
        }
        else {
            minValue = *min2;
        }
        return true;
    }

    // 删除最小值
    bool tryPopMin(float& minValue) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        if (minHeap1_.empty() && minHeap2_.empty()) {
            return false; // 两个堆都为空
        }

        // 获取两个堆的最小值
        std::optional<float> min1 = minHeap1_.empty() ? std::nullopt : std::optional<float>(minHeap1_.top());
        std::optional<float> min2 = minHeap2_.empty() ? std::nullopt : std::optional<float>(minHeap2_.top());

        // 删除全局最小值
        if (min1 && min2) {
            if (*min1 <= *min2) {
                minValue = *min1;
                minHeap1_.pop();
            }
            else {
                minValue = *min2;
                minHeap2_.pop();
            }
        }
        else if (min1) {
            minValue = *min1;
            minHeap1_.pop();
        }
        else {
            minValue = *min2;
            minHeap2_.pop();
        }
        return true;
    }

    // 获取当前存储的元素总数
    size_t size() const {
        std::shared_lock<std::shared_mutex> lock(mutex_);
        return minHeap1_.size() + minHeap2_.size();
    }

private:
    // 自定义的最小堆，底层容器为 std::vector
    std::priority_queue<float, std::vector<float>, std::greater<float>> minHeap1_; // 第一个最小堆
    std::priority_queue<float, std::vector<float>, std::greater<float>> minHeap2_; // 第二个最小堆
    mutable std::shared_mutex mutex_; // 读写锁
    size_t insertCount_ = 0; // 插入计数器，用于分片

    // 工具函数：为优先队列的底层容器预分配容量
    void reserveCapacity(std::priority_queue<float, std::vector<float>, std::greater<float>>& heap, size_t capacity) {
        std::vector<float> temp;
        temp.reserve(capacity);
        heap = std::priority_queue<float, std::vector<float>, std::greater<float>>(std::greater<float>(), std::move(temp));
    }
};