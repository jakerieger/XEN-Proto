// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma once

#include "Shared/Types.h"

class Profiler {
public:
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    Profiler()      = delete;
    static void Begin(const str& name);
    static void End();
    static void CaptureFrame();

    static TimePoint BeginContext();
    static void EndContext(TimePoint begin, const str& name);

private:
    static str mContextName;
    static Dictionary<str, std::chrono::duration<f32>> mTimedContexts;
};
