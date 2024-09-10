// Author: Jake Rieger
// Created: 9/9/2024.
//

#include "Mat4x4.h"

namespace XnMath {
    Mat4x4 Mat4x4::operator+(const Mat4x4& rhs) const {
        return {
          _mm_add_ps(Rows[0], rhs.Rows[0]),
          _mm_add_ps(Rows[1], rhs.Rows[1]),
          _mm_add_ps(Rows[2], rhs.Rows[2]),
          _mm_add_ps(Rows[3], rhs.Rows[3]),
        };
    }

    Mat4x4& Mat4x4::operator+=(const Mat4x4& rhs) {
        for (int i = 0; i < 4; ++i) {
            Rows[i] = _mm_add_ps(Rows[i], rhs.Rows[i]);
        }
        return *this;
    }

    Mat4x4 Mat4x4::operator-(const Mat4x4& rhs) const {
        return {
          _mm_sub_ps(Rows[0], rhs.Rows[0]),
          _mm_sub_ps(Rows[1], rhs.Rows[1]),
          _mm_sub_ps(Rows[2], rhs.Rows[2]),
          _mm_sub_ps(Rows[3], rhs.Rows[3]),
        };
    }

    Mat4x4& Mat4x4::operator-=(const Mat4x4& rhs) {
        for (int i = 0; i < 4; ++i) {
            Rows[i] = _mm_sub_ps(Rows[i], rhs.Rows[i]);
        }
        return *this;
    }

    Mat4x4 Mat4x4::operator*(f32 scalar) const {
        const auto s = _mm_set1_ps(scalar);
        return {
          _mm_mul_ps(Rows[0], s),
          _mm_mul_ps(Rows[1], s),
          _mm_mul_ps(Rows[2], s),
          _mm_mul_ps(Rows[3], s),
        };
    }

    Mat4x4& Mat4x4::operator*=(f32 scalar) {
        const auto s = _mm_set1_ps(scalar);
        for (auto& Row : Rows) {
            Row = _mm_mul_ps(Row, s);
        }
        return *this;
    }

    Mat4x4 Mat4x4::operator*(const Mat4x4& rhs) const {
        Mat4x4 result;
        for (int i = 0; i < 4; ++i) {
            result.Rows[i] = _mm_add_ps(
              _mm_add_ps(
                _mm_mul_ps(_mm_shuffle_ps(Rows[i], Rows[i], _MM_SHUFFLE(0, 0, 0, 0)), rhs.Rows[0]),
                _mm_mul_ps(_mm_shuffle_ps(Rows[i], Rows[i], _MM_SHUFFLE(1, 1, 1, 1)), rhs.Rows[1])),
              _mm_add_ps(
                _mm_mul_ps(_mm_shuffle_ps(Rows[i], Rows[i], _MM_SHUFFLE(2, 2, 2, 2)), rhs.Rows[2]),
                _mm_mul_ps(_mm_shuffle_ps(Rows[i], Rows[i], _MM_SHUFFLE(3, 3, 3, 3)),
                           rhs.Rows[3])));
        }
        return result;
    }

    Mat4x4& Mat4x4::operator*=(const Mat4x4& rhs) {
        *this = *this * rhs;
        return *this;
    }

    void Mat4x4::SetRow(int row, const f32* values) {
        if (row > 3 || row < 0) {
            throw RuntimeError("Row index out of bounds");
        }

        Rows[row] = _mm_setr_ps(values[0], values[1], values[2], values[3]);
    }

    Mat4x4& Mat4x4::Transpose() {
        _MM_TRANSPOSE4_PS(Rows[0], Rows[1], Rows[2], Rows[3]);
        return *this;
    }

    Mat4x4 Mat4x4::Identity() {
        return {
          _mm_set_ps(0.f, 0.f, 0.f, 1.f),
          _mm_set_ps(0.f, 0.f, 1.f, 0.f),
          _mm_set_ps(0.f, 1.f, 0.f, 0.f),
          _mm_set_ps(1.f, 0.f, 0.f, 0.f),
        };
    }

    f32 Mat4x4::SDeterminant() const {
        const f32 det = M[0][0] * (M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                                   M[1][2] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) +
                                   M[1][3] * (M[2][1] * M[3][2] - M[2][2] * M[3][1])) -
                        M[0][1] * (M[1][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                                   M[1][2] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) +
                                   M[1][3] * (M[2][0] * M[3][2] - M[2][2] * M[3][0])) +
                        M[0][2] * (M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
                                   M[1][1] * (M[2][0] * M[3][3] - M[2][3] * M[3][0]) +
                                   M[1][3] * (M[2][0] * M[3][1] - M[2][1] * M[3][0])) -
                        M[0][3] * (M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
                                   M[1][1] * (M[2][0] * M[3][2] - M[2][2] * M[3][0]) +
                                   M[1][2] * (M[2][0] * M[3][1] - M[2][1] * M[3][0]));
        return det;
    }

    f32 Mat4x4::FDeterminant() const {
        // Load rows into SIMD registers
        __m128 r0 = Rows[0];
        __m128 r1 = Rows[1];
        __m128 r2 = Rows[2];
        __m128 r3 = Rows[3];

        // Calculate the 3x3 determinants for cofactors
        __m128 r1r2r3 = _mm_set_ps(r3.m128_f32[2], r2.m128_f32[2], r1.m128_f32[2], r0.m128_f32[2]);
        __m128 r1r2r3_x =
          _mm_set_ps(r3.m128_f32[0], r2.m128_f32[0], r1.m128_f32[0], r0.m128_f32[0]);
        __m128 r1r2r3_y =
          _mm_set_ps(r3.m128_f32[1], r2.m128_f32[1], r1.m128_f32[1], r0.m128_f32[1]);

        // Compute the minor determinants
        __m128 subFactor0 = _mm_sub_ps(_mm_mul_ps(r2, r3), _mm_mul_ps(r3, r2));
        __m128 subFactor1 = _mm_sub_ps(_mm_mul_ps(r1r2r3_x, r2), _mm_mul_ps(r1r2r3_y, r3));
        __m128 subFactor2 = _mm_sub_ps(_mm_mul_ps(r1r2r3_y, r2), _mm_mul_ps(r1r2r3_x, r3));
        __m128 subFactor3 = _mm_sub_ps(_mm_mul_ps(r1r2r3_x, r2), _mm_mul_ps(r1r2r3_y, r3));

        // Combine the cofactors to get the determinant
        __m128 temp0 = _mm_add_ps(_mm_mul_ps(r0, subFactor0), _mm_mul_ps(r1, subFactor1));
        __m128 temp1 = _mm_add_ps(_mm_mul_ps(r2, subFactor2), _mm_mul_ps(r3, subFactor3));
        __m128 det   = _mm_add_ps(temp0, temp1);

        // Extract the result from the SIMD register
        return _mm_cvtss_f32(det);
    }
}  // namespace XnMath