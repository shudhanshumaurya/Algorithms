// filepath: c:\Users\USER1\Algorithms\Algorithms\ThreadSafeQueue\main.cpp
#include "Queue.hpp"
#include <thread>
#include <chrono>
#include <iostream>

int main() {
    ThreadSafeQueue<int> tsq;

    // Producer thread
    std::thread producer([&tsq]() {
        for (int i = 0; i < 10; ++i) {
            tsq.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    // Consumer thread
    std::thread consumer([&tsq]() {
        for (int i = 0; i < 10; ++i) {
            int value;
            if (tsq.pop(value)) {
                std::cout << "Consumed: " << value << std::endl;
            }
        }
    });

    producer.join();
    consumer.join();

    return 0;
}