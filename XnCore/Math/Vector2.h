// Author: Jake Rieger
// Created: 8/27/2024.
//

#pragma once

#include "Shared/Types.h"

#include <immintrin.h>

/// @brief SIMD-optimized 2D vector class
class Vector2 {
public:
    union {
        __m128 m128_f32;
        struct {
            f32 X;
            f32 Y;
            f32 _pad1;  // Padding for alignment
            f32 _pad2;  // Padding for alignment
        };
    };

    // Constructors
    Vector2() : m128_f32(_mm_setzero_ps()) {}

    Vector2(f32 x, f32 y) : m128_f32(_mm_set_ps(0.f, 0.f, y, x)) {}

    Vector2(const Vector2& other) : m128_f32(other.m128_f32) {}

    // Addition
    Vector2 operator+(const Vector2& rhs) const;

    Vector2& operator+=(const Vector2& rhs);

    // Subtraction
    Vector2 operator-(const Vector2& rhs) const;

    Vector2& operator-=(const Vector2& rhs);

    // Multiplication by a scalar
    Vector2 operator*(f32 scalar) const;

    Vector2& operator*=(f32 scalar);

    // Dot product
    [[nodiscard]] f32 Dot(const Vector2& rhs) const;

    // Length (magnitude)
    [[nodiscard]] f32 Length() const;

    // Normalize
    [[nodiscard]] Vector2 Normalize() const;

private:
    explicit Vector2(const __m128& other) : m128_f32(other) {}
};