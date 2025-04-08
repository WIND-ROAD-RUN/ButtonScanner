#include <iostream>
#include <thread>
#include <vector>
#include "dsl_PriorityQueue.hpp"

// ����������̺߳���
void insertElements(rw::dsl::ThreadSafeDHeap<int, int>& pq, int start, int count) {
    for (int i = 0; i < count; ++i) {
        pq.insert(start + i, start + i); // ����Ԫ�ؼ������ȼ�
        std::cout << "Inserted: " << (start + i) << " with priority " << (start + i) << std::endl;
    }
}

// ɾ���������̺߳���
void removeElements(rw::dsl::ThreadSafeDHeap<int, int>& pq, int start, int count) {
    for (int i = 0; i < count; ++i) {
        try {
            int topElement = pq.top(); // ��ȡ��ɾ��������ȼ���Ԫ��
            std::cout << "Removed: " << topElement << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cout << "Remove failed: " << e.what() << std::endl;
        }
    }
}

// ���²������̺߳���
void updateElements(rw::dsl::ThreadSafeDHeap<int, int>& pq, int start, int count) {
    for (int i = 0; i < count; ++i) {
        pq.update(start + i, start + i + 100); // �������ȼ�
        std::cout << "Updated: " << (start + i) << " to new priority " << (start + i + 100) << std::endl;
    }
}

int main() {
    // ����һ���̰߳�ȫ�����ȶ���
    rw::dsl::ThreadSafeDHeap<int, int> pq;

    // ��������߳�
    std::thread t1(insertElements, std::ref(pq), 1, 5);  // ���� 5 ��Ԫ��
    std::thread t2(insertElements, std::ref(pq), 6, 5);  // �������� 5 ��Ԫ��
    std::thread t3(removeElements, std::ref(pq), 1, 5);  // ɾ�� 5 ��Ԫ��
    std::thread t4(updateElements, std::ref(pq), 1, 5);  // ����ǰ 5 ��Ԫ�ص����ȼ�

    // �ȴ������߳����
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // ��ӡ���ն��еĴ�С
    std::cout << "Final size of priority queue: " << pq.size() << std::endl;

    return 0;
}