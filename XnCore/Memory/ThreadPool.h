// Author: Jake Rieger
// Created: 8/20/2024.
//

#pragma once

#include "Types.h"

#include <condition_variable>

class ThreadPool {
public:
    explicit ThreadPool(int numThreads);
    ~ThreadPool();

    template<class F, class... Args>
    auto Enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result_t<F, Args...>> {
        using ReturnType = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<ReturnType()>>(
          std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<ReturnType> result = task->get_future();
        {
            std::unique_lock<Mutex> lock(mMutex);
            mTasks.emplace([task]() { (*task)(); });
        }
        mCondition.notify_one();
        return result;
    }

    static u32 GetMaxThreadCount();

private:
    Vector<Thread> mWorkers;
    Queue<std::function<void()>> mTasks {};
    Mutex mMutex;
    std::condition_variable mCondition;
    Atomic<bool> mStop;
};
