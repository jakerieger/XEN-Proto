// Author: Jake Rieger
// Created: 8/28/2024.
//

#include "Matrix4x4.h"

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs) const {
    return {
      _mm_add_ps(Rows[0], rhs.Rows[0]),
      _mm_add_ps(Rows[1], rhs.Rows[1]),
      _mm_add_ps(Rows[2], rhs.Rows[2]),
      _mm_add_ps(Rows[3], rhs.Rows[3]),
    };
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs) {
    for (int i = 0; i < 4; ++i) {
        Rows[i] = _mm_add_ps(Rows[i], rhs.Rows[i]);
    }
    return *this;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs) const {
    return {
      _mm_sub_ps(Rows[0], rhs.Rows[0]),
      _mm_sub_ps(Rows[1], rhs.Rows[1]),
      _mm_sub_ps(Rows[2], rhs.Rows[2]),
      _mm_sub_ps(Rows[3], rhs.Rows[3]),
    };
}

Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs) {
    for (int i = 0; i < 4; ++i) {
        Rows[i] = _mm_sub_ps(Rows[i], rhs.Rows[i]);
    }
    return *this;
}

Matrix4x4 Matrix4x4::operator*(f32 scalar) const {
    const auto scalarSimd = _mm_set1_ps(scalar);
    return {
      _mm_mul_ps(Rows[0], scalarSimd),
      _mm_mul_ps(Rows[1], scalarSimd),
      _mm_mul_ps(Rows[2], scalarSimd),
      _mm_mul_ps(Rows[3], scalarSimd),
    };
}

Matrix4x4& Matrix4x4::operator*=(f32 scalar) {
    const auto scalarSimd = _mm_set1_ps(scalar);
    for (auto& Row : Rows) {
        Row = _mm_mul_ps(Row, scalarSimd);
    }
    return *this;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        result.Rows[i] = _mm_add_ps(
          _mm_add_ps(
            _mm_mul_ps(_mm_shuffle_ps(Rows[i], Rows[i], _MM_SHUFFLE(0, 0, 0, 0)), rhs.Rows[0]),
            _mm_mul_ps(_mm_shuffle_ps(Rows[i], Rows[i], _MM_SHUFFLE(1, 1, 1, 1)), rhs.Rows[1])),
          _mm_add_ps(
            _mm_mul_ps(_mm_shuffle_ps(Rows[i], Rows[i], _MM_SHUFFLE(2, 2, 2, 2)), rhs.Rows[2]),
            _mm_mul_ps(_mm_shuffle_ps(Rows[i], Rows[i], _MM_SHUFFLE(3, 3, 3, 3)), rhs.Rows[3])));
    }
    return result;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs) {
    *this = *this * rhs;
    return *this;
}

Matrix4x4 Matrix4x4::Transpose() {
    Matrix4x4 result;
    _MM_TRANSPOSE4_PS(result.Rows[0], result.Rows[1], result.Rows[2], result.Rows[3]);
    return result;
}

Matrix4x4 Matrix4x4::Identity() {
    return {
      _mm_set_ps(0.f, 0.f, 0.f, 1.f),
      _mm_set_ps(0.f, 0.f, 1.f, 0.f),
      _mm_set_ps(0.f, 1.f, 0.f, 0.f),
      _mm_set_ps(1.f, 0.f, 0.f, 0.f),
    };
}

f32 Matrix4x4::Determinant() const {
    const float subFactor00 = M[2][2] * M[3][3] - M[3][2] * M[2][3];
    const float subFactor01 = M[2][1] * M[3][3] - M[3][1] * M[2][3];
    const float subFactor02 = M[2][1] * M[3][2] - M[3][1] * M[2][2];
    const float subFactor03 = M[2][0] * M[3][3] - M[3][0] * M[2][3];
    const float subFactor04 = M[2][0] * M[3][2] - M[3][0] * M[2][2];
    const float subFactor05 = M[2][0] * M[3][1] - M[3][0] * M[2][1];

    const float detCof = M[1][0] * subFactor00 - M[1][1] * subFactor03 + M[1][2] * subFactor05;

    return M[0][0] * detCof -
           M[0][1] * (M[1][0] * subFactor01 - M[1][1] * subFactor03 + M[1][2] * subFactor04) +
           M[0][2] * (M[1][0] * subFactor02 - M[1][1] * subFactor04 + M[1][2] * subFactor05);
}