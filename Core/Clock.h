// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "Shared/Types.h"

class Clock {
public:
    Clock() = default;

    [[nodiscard]] f32 GetDeltaTime() const;
    [[nodiscard]] f32 GetFrameTime() const;
    [[nodiscard]] i64 GetTotalTime() const;
    [[nodiscard]] f32 GetFrameRate() const;

    void Start();
    void Stop();
    void Tick();
    void Update();

private:
    using ClockTime = std::chrono::time_point<std::chrono::steady_clock>;

    bool mRunning  = false;
    f32 mDeltaTime = 0;
    f32 mFrameTime = 0;
    ClockTime mLastTime;
    ClockTime mStartTime;
};
