// Author: Jake Rieger
// Created: 8/27/2024.
//

#pragma once

#include "Shared/Types.h"

static void Normalize(Vector<f32>& samples, const f32 targetPeak) {
    if (samples.empty())
        return;

    f32 maxAbsValue = 0.f;
    for (const f32 sample : samples) {
        maxAbsValue = std::max(maxAbsValue, std::abs(sample));
    }
    const f32 scale = targetPeak / maxAbsValue;
    for (f32& sample : samples) {
        sample *= scale;
    }
}

static i32 MakeMultiple(const i32 number, const i32 multiple) {
    const i32 remainder = number % multiple;
    const i32 diff      = multiple - remainder;
    return number + diff;
}

template<typename T>
Vector<T> Interleave(const Vector<T>& vecA, const Vector<T>& vecB) {
    Vector<T> result;
    const size_t size = std::min(vecA.size(), vecB.size());

    for (size_t i = 0; i < size; ++i) {
        result.push_back(vecA[i]);
        result.push_back(vecB[i]);
    }

    for (size_t i = size; i < vecA.size(); ++i) {
        result.push_back(vecA[i]);
    }
    for (size_t i = size; i < vecB.size(); ++i) {
        result.push_back(vecB[i]);
    }

    return result;
}