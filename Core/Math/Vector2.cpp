// Author: Jake Rieger
// Created: 8/27/2024.
//

#include "Vector2.h"

#include <cmath>

Vector2 Vector2::operator+(const Vector2& rhs) const {
    return Vector2(_mm_add_ps(m128_f32, rhs.m128_f32));
}

Vector2& Vector2::operator+=(const Vector2& rhs) {
    m128_f32 = _mm_add_ps(m128_f32, rhs.m128_f32);
    return *this;
}

Vector2 Vector2::operator-(const Vector2& rhs) const {
    return Vector2(_mm_sub_ps(m128_f32, rhs.m128_f32));
}

Vector2& Vector2::operator-=(const Vector2& rhs) {
    m128_f32 = _mm_sub_ps(m128_f32, rhs.m128_f32);
    return *this;
}

Vector2 Vector2::operator*(float scalar) const {
    const auto scalarSimd = _mm_set1_ps(scalar);
    return Vector2(_mm_mul_ps(m128_f32, scalarSimd));
}

Vector2& Vector2::operator*=(float scalar) {
    const auto scalarSimd = _mm_set1_ps(scalar);
    m128_f32              = _mm_mul_ps(m128_f32, scalarSimd);
    return *this;
}

float Vector2::Dot(const Vector2& rhs) const {
    auto mul = _mm_mul_ps(m128_f32, rhs.m128_f32);
    // Shuffle and add
    mul = _mm_hadd_ps(mul, mul);
    return _mm_cvtss_f32(mul);
}

float Vector2::Length() const {
    return std::sqrt(Dot(*this));
}

Vector2 Vector2::Normalize() const {
    const float len = Length();
    if (len == 0.f)
        return {0.f, 0.f};
    return *this * (1.f / len);
}