#pragma once
#include <atomic>

template<typename T>
class LockFreeQueue {
private:
    struct Node {
        T value;
        std::atomic<Node*> next;

        Node(T val) : value(val), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    LockFreeQueue();
    ~LockFreeQueue();

    void enqueue(const T& value);
    bool dequeue(T& result);
};