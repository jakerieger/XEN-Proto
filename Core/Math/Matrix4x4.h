// Author: Jake Rieger
// Created: 8/28/2024.
//

#pragma once

#include "Shared/Types.h"

#include <immintrin.h>
#include <cmath>

/// @brief SIMD-optimized 4x4 matrix class.
class Matrix4x4 {
public:
    union {
        __m128 Rows[4];  // Each row of the matrix is stored in a 128-bit SIMD register
        f32 M[4][4];     // Access to individual elements of the matrix
    };

    Matrix4x4() {
        for (auto& Row : Rows) {
            Row = _mm_setzero_ps();
        }
    }

    explicit Matrix4x4(const f32 values[4][4]) {
        for (int i = 0; i < 4; ++i) {
            Rows[i] = _mm_loadu_ps(values[i]);
        }
    }

    Matrix4x4(const Matrix4x4& other) {
        Rows[0] = other.Rows[0];
        Rows[1] = other.Rows[1];
        Rows[2] = other.Rows[2];
        Rows[3] = other.Rows[3];
    }

    Matrix4x4 operator+(const Matrix4x4& rhs) const;

    Matrix4x4& operator+=(const Matrix4x4& rhs);

    Matrix4x4 operator-(const Matrix4x4& rhs) const;

    Matrix4x4& operator-=(const Matrix4x4& rhs);

    Matrix4x4 operator*(f32 scalar) const;

    Matrix4x4& operator*=(f32 scalar);

    // Matrix multiplication
    Matrix4x4 operator*(const Matrix4x4& rhs) const;

    Matrix4x4& operator*=(const Matrix4x4& rhs);

    // Transpose
    static Matrix4x4 Transpose();

    // Identity matrix
    static Matrix4x4 Identity();

    // Determinant (simple method, not optimized)
    [[nodiscard]] f32 Determinant() const;

private:
    // Private constructor for internal use with SIMD rows
    Matrix4x4(const __m128& row0, const __m128& row1, const __m128& row2, const __m128& row3) {
        Rows[0] = row0;
        Rows[1] = row1;
        Rows[2] = row2;
        Rows[3] = row3;
    }
};
