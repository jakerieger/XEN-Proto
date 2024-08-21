// Author: Jake Rieger
// Created: 8/20/2024.
//

#pragma once

#include "Shared/Types.h"
#include <condition_variable>

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();

    template<class F>
    void Enqueue(F&& task);

    static u32 GetMaxThreadCount();

private:
    Vector<Thread> mWorkers;
    Queue<std::function<void()>> mTasks {};
    Mutex mMutex;
    std::condition_variable mCondition;
    Atomic<bool> mStop;
};
