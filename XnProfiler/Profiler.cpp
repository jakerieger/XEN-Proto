// Author: Jake Rieger
// Created: 9/1/2024.
//

#include "Profiler.h"

#include <iostream>

Dictionary<str, std::chrono::duration<f32>> Profiler::mTimedContexts = {};
str Profiler::mContextName                                           = "Profiler";

void Profiler::Begin(const str& name) {
    mContextName = name;
}

void Profiler::End() {
    mTimedContexts.clear();
}

void Profiler::CaptureFrame() {
    for (auto& [name, duration] : mTimedContexts) {
        std::cout << "[" << mContextName << "] " << name << ": " << duration.count() * 1000 << " ms"
                  << "\n";
    }

    std::cout << std::endl;
}

Profiler::TimePoint Profiler::BeginContext() {
    return std::chrono::high_resolution_clock::now();
}

void Profiler::EndContext(TimePoint begin, const str& name) {
    mTimedContexts[name] =
      std::chrono::duration<f32>(std::chrono::high_resolution_clock::now() - begin);
}