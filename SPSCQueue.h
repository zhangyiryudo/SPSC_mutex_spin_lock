#ifndef SPSC_QUEUE_H
#define SPSC_QUEUE_H

#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <vector>

using namespace std;

// Single-producer, single-consumer queue using mutex + condition variable.
// The implementation is explicitly instantiated for int in SPSCQueue.cpp.

template <typename T>
class SPSCQueue {
public:
    explicit SPSCQueue(size_t capacity);
    ~SPSCQueue() = default;

    void push(T value);
    bool pop(T& out);
    void close();

private:
    const size_t capacity_;
    vector<T> buffer_;
    size_t head_;
    size_t tail_;
    size_t size_;
    bool closed_;
    mutex mutex_;
    condition_variable producer_cv_;
    condition_variable consumer_cv_;
};

#endif // SPSC_QUEUE_H
