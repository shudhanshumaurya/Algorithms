#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <stdexcept>

template<typename T>
class ThreadSafeQueue {
    
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_var_;
    std::atomic<bool> stop_{false};

public:
   
   // Default constructor
    ThreadSafeQueue() = default;

   // Deleting Copy constructor and assignment operator
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    void push(const T& value){
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(value));
        }
        cond_var_.notify_one();
    }

    bool pop(T& value){
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [this](){ return !queue_.empty() || stop_.load(); });

        if(stop_.load() && queue_.empty()) {
            throw std::runtime_error("Queue stopped and empty");
        }
        value = std::move(queue_.front());
        queue_.pop();
        return true;
    }
};