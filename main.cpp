#include "SPSCQueue.h"
#include <iostream>
#include <thread>

using namespace std;

int main() {
    const size_t message_count = 100000;
    const size_t queue_capacity = 1024;

    SPSCQueue<int> queue(queue_capacity);
    thread producer([&queue, message_count]() {
        for (int i = 1; i <= static_cast<int>(message_count); ++i) {
            queue.push(i);
        }
        queue.close();
    });

    thread consumer([&queue]() {
        int value;
        size_t received = 0;
        long long sum = 0;
        while (queue.pop(value)) {
            sum += value;
            ++received;
        }
        cout << "Consumer received " << received << " values, sum=" << sum << "\n";
    });

    producer.join();
    consumer.join();

    cout << "SPSC queue demo finished." << endl;
    return 0;
}
