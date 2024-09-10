// Author: Jake Rieger
// Created: 9/9/2024.
//

#pragma once

#include <Types.h>
#include <immintrin.h>

namespace XnMath {
    class Vec2 {
    public:
        union alignas(16) {   // Enforce 16-byte alignment
            __m128 m128_f32;  // SSE register containing four single-precision (32-bit) floats
            struct {
                f32 X;      // First component v₁
                f32 Y;      // Second component v₂
                f32 _pad1;  // Padding to align with 128-bit register
                f32 _pad2;  // Padding to align with 128-bit register
            };
        };

        // Constructors
        Vec2() : m128_f32(_mm_setzero_ps()) {}
        Vec2(f32 x, f32 y) : m128_f32(_mm_set_ps(0.f, 0.f, y, x)) {}
        Vec2(const Vec2& other) : m128_f32(other.m128_f32) {}

        // Addition
        Vec2 operator+(const Vec2& rhs) const;
        Vec2& operator+=(const Vec2& rhs);

        // Subtraction
        Vec2 operator-(const Vec2& rhs) const;
        Vec2& operator-=(const Vec2& rhs);

        // Multiplication (dot product)
        f32 operator*(const Vec2& rhs) const;

        // Multiplication (scalar)
        Vec2 operator*(f32 scalar) const;
        Vec2& operator*=(f32 scalar);

        // Dot product
        [[nodiscard]] f32 Dot(const Vec2& rhs) const;

        // Length (magnitude)
        [[nodiscard]] f32 Length() const;

        // Normalize
        [[nodiscard]] Vec2 Normalize() const;

    private:
        // Private constructor used to assign 128-bit registers directly. Not intended
        // for external use.
        explicit Vec2(const __m128& other) : m128_f32(other) {}
    };
}  // namespace XnMath
