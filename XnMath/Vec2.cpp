// Author: Jake Rieger
// Created: 9/9/2024.
//

#include "Vec2.h"

#include <cmath>

namespace XnMath {
    Vec2 Vec2::operator+(const Vec2& rhs) const {
        return Vec2(_mm_add_ps(m128_f32, rhs.m128_f32));
    }

    Vec2& Vec2::operator+=(const Vec2& rhs) {
        m128_f32 = _mm_add_ps(m128_f32, rhs.m128_f32);
        return *this;
    }

    Vec2 Vec2::operator-(const Vec2& rhs) const {
        return Vec2(_mm_sub_ps(m128_f32, rhs.m128_f32));
    }

    Vec2& Vec2::operator-=(const Vec2& rhs) {
        m128_f32 = _mm_sub_ps(m128_f32, rhs.m128_f32);
        return *this;
    }

    f32 Vec2::operator*(const Vec2& rhs) const {
        return Dot(rhs);
    }

    Vec2 Vec2::operator*(f32 scalar) const {
        const auto scalarVec = _mm_set1_ps(scalar);
        return Vec2(_mm_mul_ps(m128_f32, scalarVec));
    }

    Vec2& Vec2::operator*=(f32 scalar) {
        const auto scalarVec = _mm_set1_ps(scalar);
        m128_f32             = _mm_mul_ps(m128_f32, scalarVec);
        return *this;
    }

    f32 Vec2::Dot(const Vec2& rhs) const {
        auto mul = _mm_mul_ps(m128_f32, rhs.m128_f32);
        // Shuffle and add
        mul = _mm_hadd_ps(mul, mul);
        return _mm_cvtss_f32(mul);
    }

    f32 Vec2::Length() const {
        return std::sqrt(Dot(*this));
    }

    Vec2 Vec2::Normalize() const {
        const f32 len = Length();
        if (len == 0.f)
            return {0.f, 0.f};
        return *this * (1.f / len);
    }
}  // namespace XnMath