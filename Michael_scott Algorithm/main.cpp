#include <iostream>
#include <thread>
#include "LockFreeQueue.hpp"

int main() {
    LockFreeQueue<int> q;

    std::thread producer([&]() {
        for (int i = 1; i <= 10; i++) {
            q.enqueue(i);
            std::cout << "Enqueued: " << i << std::endl;
        }
    });

    std::thread consumer([&]() {
        int value;
        for (int i = 0; i < 10; i++) {
            while (!q.dequeue(value)); // spin
            std::cout << "Dequeued: " << value << std::endl;
        }
    });

    producer.join();
    consumer.join();

    return 0;
}