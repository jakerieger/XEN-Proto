// Author: Jake Rieger
// Created: 8/20/2024.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads) {
    for (auto i = 0; i < numThreads; i++) {
        mWorkers.emplace_back([this] {
            while (!mStop) {
                Function<void()> task;
                {
                    std::unique_lock<Mutex> lock(mMutex);
                    this->mCondition.wait(lock,
                                          [this] { return this->mStop || !mWorkers.empty(); });
                    if (this->mStop && this->mTasks.empty())
                        return;
                    task = std::move(this->mTasks.front());
                    this->mTasks.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    mStop = true;
    mCondition.notify_all();
    for (Thread& worker : mWorkers) {
        worker.join();
    }
}
u32 ThreadPool::GetMaxThreadCount() {
    return 4;
}

template<class F>
void ThreadPool::Enqueue(F&& task) {
    {
        std::unique_lock<Mutex> lock(mMutex);
        mTasks.emplace(std::forward<F>(task));
    }
    mCondition.notify_one();
}