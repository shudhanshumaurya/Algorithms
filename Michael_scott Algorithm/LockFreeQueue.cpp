#include "LockFreeQueue.hpp"

template<typename T>
LockFreeQueue<T>::LockFreeQueue() {
    Node* dummy = new Node(T{});
    head.store(dummy);
    tail.store(dummy);
}

template<typename T>
LockFreeQueue<T>::~LockFreeQueue() {
    T temp;
    while (dequeue(temp));
    delete head.load();
}

template<typename T>
void LockFreeQueue<T>::enqueue(const T& value) {
    Node* newNode = new Node(value);

    while (true) {
        Node* last = tail.load(std::memory_order_acquire);
        Node* next = last->next.load(std::memory_order_acquire);

        if (last == tail.load(std::memory_order_acquire)) {
            if (next == nullptr) {
                if (last->next.compare_exchange_weak(next, newNode)) {
                    tail.compare_exchange_weak(last, newNode);
                    return;
                }
            } else {
                tail.compare_exchange_weak(last, next);
            }
        }
    }
}

template<typename T>
bool LockFreeQueue<T>::dequeue(T& result) {
    while (true) {
        Node* first = head.load(std::memory_order_acquire);
        Node* last  = tail.load(std::memory_order_acquire);
        Node* next  = first->next.load(std::memory_order_acquire);

        if (first == head.load(std::memory_order_acquire)) {
            if (first == last) {
                if (next == nullptr) {
                    return false; // empty
                }
                tail.compare_exchange_weak(last, next);
            } else {
                result = next->value;
                if (head.compare_exchange_weak(first, next)) {
                    delete first; // unsafe in real systems
                    return true;
                }
            }
        }
    }
}

template class LockFreeQueue<int>;