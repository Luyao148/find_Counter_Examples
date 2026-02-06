#include "ThreadPool.h"

ThreadPool::ThreadPool(std::size_t threadCount)
    : _pool(std::make_shared<Pool>()) {
    assert(threadCount > 0);
    for (std::size_t i = 0; i < threadCount; ++i) {
        _pool->threads.emplace_back([pool = _pool]() {
            std::unique_lock<std::mutex> locker(pool->mtx);
            while (true) {
                pool->cv.wait(locker, [pool] {
                    return !pool->tasks.empty() || pool->isOver;
                });
                if (pool->isOver && pool->tasks.empty())
                    return;
                auto task = std::move(pool->tasks.front());
                pool->tasks.pop();
                locker.unlock();
                task();
                locker.lock();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> locker(_pool->mtx);
        _pool->isOver = true;
    }
    _pool->cv.notify_all();
    for (auto &t : _pool->threads) {
        t.join();
    }
}