#pragma once

#include <cstddef>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <utility>
#include <cassert>
#include <vector>

class ThreadPool{
public:
    explicit ThreadPool(std::size_t threadCount=8);

    ThreadPool() = delete;

    ThreadPool(ThreadPool&&) = delete;

    ~ThreadPool();

    template<class F>
    void addTask(F&& task){
        {
            std::lock_guard<std::mutex> locker(_pool->mtx);
            _pool->tasks.emplace(std::forward<F>(task));
        }
        _pool->cv.notify_one();
    }

private:
    struct Pool{
        std::mutex mtx;
        std::condition_variable cv;
        bool isOver=false;
        std::queue<std::function<void()>> tasks;
        std::vector<std::thread> threads;
    };
    std::shared_ptr<Pool> _pool;
};