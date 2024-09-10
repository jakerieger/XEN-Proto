// Author: Jake Rieger
// Created: 9/9/2024.
//

#pragma once

#include "Vec2.h"
#include "Vec3.h"

#define ASSERT_VECTOR                                                                              \
    static_assert(std::is_base_of_v<Vec2, T> || std::is_base_of_v<Vec3, T>,                        \
                  "T must be a vector type (either Vec2 or Vec3)");

namespace XnMath {
    template<typename T>
    f32 Dot(const T& lhs, const T& rhs) {
        ASSERT_VECTOR
        return lhs * rhs;
    }

    inline Vec3 Cross(const Vec3& lhs, const Vec3& rhs) {
        return lhs.Cross(rhs);
    }

    template<typename T>
    T Normalize(const T& vec) {
        ASSERT_VECTOR
        return vec.Normalize();
    }
}  // namespace XnMath
