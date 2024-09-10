// Author: Jake Rieger
// Created: 9/9/2024.
//

#pragma once

#include <Types.h>
#include <immintrin.h>

namespace XnMath {
    class Vec3 {
    public:
        union alignas(16) {   // Enforce 16-byte alignment
            __m128 m128_f32;  // SSE register containing four single-precision (32-bit) floats
            struct {
                f32 X;      // First component v₁
                f32 Y;      // Second component v₂
                f32 Z;      // Third component v₃
                f32 _pad1;  // Padding to align with 128-bit register
            };
        };

        // Constructors
        Vec3() : m128_f32(_mm_setzero_ps()) {}
        Vec3(f32 x, f32 y, f32 z) : m128_f32(_mm_set_ps(0.f, z, y, x)) {}
        Vec3(const Vec3& other) : m128_f32(other.m128_f32) {}

        // Addition
        Vec3 operator+(const Vec3& rhs) const;
        Vec3& operator+=(const Vec3& rhs);

        // Subtraction
        Vec3 operator-(const Vec3& rhs) const;
        Vec3& operator-=(const Vec3& rhs);

        // Multiplication (dot product)
        f32 operator*(const Vec3& rhs) const;

        // Multiplication (scalar)
        Vec3 operator*(f32 scalar) const;
        Vec3& operator*=(f32 scalar);

        // Dot product
        [[nodiscard]] f32 Dot(const Vec3& rhs) const;

        // Cross product
        [[nodiscard]] Vec3 Cross(const Vec3& rhs) const;

        // Length (magnitude)
        [[nodiscard]] f32 Length() const;

        // Normalize
        [[nodiscard]] Vec3 Normalize() const;

    private:
        // Private constructor used to assign 128-bit registers directly. Not intended
        // for external use.
        explicit Vec3(const __m128& other) : m128_f32(other) {}
    };
}  // namespace XnMath
