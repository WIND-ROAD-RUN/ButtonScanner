#include <iostream>
#include <thread>
#include <vector>
#include "dsl_PriorityQueue.hpp"

int main() {
	rw::dsl::ThreadSafeDHeap<float, float> deque;
	deque.insert(-213, -123);
	deque.insert(123, 123);

	return 0;
}