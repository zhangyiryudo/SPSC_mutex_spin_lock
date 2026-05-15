#include "SPSCQueue.h"
#include <stdexcept>

using namespace std;

template <typename T>
SPSCQueue<T>::SPSCQueue(size_t capacity)
    : capacity_(capacity), buffer_(capacity), head_(0), tail_(0), size_(0), closed_(false) {}

template <typename T>
void SPSCQueue<T>::push(T value) {
    unique_lock<mutex> lock(mutex_);
    producer_cv_.wait(lock, [this] { return size_ < capacity_ || closed_; });
    if (closed_) {
        throw runtime_error("push to closed queue");
    }

    buffer_[tail_] = std::move(value);
    tail_ = (tail_ + 1) % capacity_;
    ++size_;
    consumer_cv_.notify_one();
}

template <typename T>
bool SPSCQueue<T>::pop(T& out) {
    unique_lock<mutex> lock(mutex_);
    consumer_cv_.wait(lock, [this] { return size_ > 0 || closed_; });
    if (size_ == 0) {
        return false;
    }

    out = move(buffer_[head_]);
    head_ = (head_ + 1) % capacity_;
    --size_;
    producer_cv_.notify_one();
    return true;
}

template <typename T>
void SPSCQueue<T>::close() {
    lock_guard<mutex> lock(mutex_);
    closed_ = true;
    consumer_cv_.notify_all();
    producer_cv_.notify_all();
}

template class SPSCQueue<int>;
