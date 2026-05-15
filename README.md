# SPSC_mutex_spin_lock

A simple C++ example demonstrating a multi-threaded single-producer/single-consumer queue using `std::mutex` and `std::condition_variable`.

## Build

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

## Run

```bash
./spsc_mutex_queue
```
