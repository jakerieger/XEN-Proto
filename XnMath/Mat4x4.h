// Author: Jake Rieger
// Created: 9/9/2024.
//

#pragma once

#include <Types.h>
#include <immintrin.h>

namespace XnMath {
    class Mat4x4 {
    public:
        union alignas(16) {  // Enforce 16-byte alignment
            __m128 Rows[4];
            f32 M[4][4];
        };

        Mat4x4() {
            for (auto& row : Rows) {
                row = _mm_setzero_ps();
            }
        }

        explicit Mat4x4(const f32 values[4][4]) {
            for (int i = 0; i < 4; ++i) {
                Rows[i] = _mm_loadu_ps(values[i]);
            }
        }

        Mat4x4(const Mat4x4& other) {
            for (int i = 0; i < 4; ++i) {
                Rows[i] = other.Rows[i];
            }
        }

        Mat4x4(const __m128& row0, const __m128& row1, const __m128& row2, const __m128& row3) {
            Rows[0] = row0;
            Rows[1] = row1;
            Rows[2] = row2;
            Rows[3] = row3;
        }

        Mat4x4 operator+(const Mat4x4& rhs) const;

        Mat4x4& operator+=(const Mat4x4& rhs);

        Mat4x4 operator-(const Mat4x4& rhs) const;

        Mat4x4& operator-=(const Mat4x4& rhs);

        Mat4x4 operator*(f32 scalar) const;

        Mat4x4& operator*=(f32 scalar);

        // Matrix multiplication
        Mat4x4 operator*(const Mat4x4& rhs) const;

        Mat4x4& operator*=(const Mat4x4& rhs);

        void SetRow(int row, const f32* values);

        // Transpose
        Mat4x4& Transpose();

        // Identity matrix
        static Mat4x4 Identity();

        // Determinant (simple method, not optimized)
        [[nodiscard]] f32 SlowDeterminant() const;
        [[nodiscard]] f32 FastDeterminant() const;
    };
}  // namespace XnMath
