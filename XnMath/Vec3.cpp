// Author: Jake Rieger
// Created: 9/9/2024.
//

#include "Vec3.h"

namespace XnMath {
    Vec3 Vec3::operator+(const Vec3& rhs) const {
        return Vec3(_mm_add_ps(m128_f32, rhs.m128_f32));
    }

    Vec3& Vec3::operator+=(const Vec3& rhs) {
        m128_f32 = _mm_add_ps(m128_f32, rhs.m128_f32);
        return *this;
    }

    Vec3 Vec3::operator-(const Vec3& rhs) const {
        return Vec3(_mm_sub_ps(m128_f32, rhs.m128_f32));
    }

    Vec3& Vec3::operator-=(const Vec3& rhs) {
        m128_f32 = _mm_sub_ps(m128_f32, rhs.m128_f32);
        return *this;
    }

    f32 Vec3::operator*(const Vec3& rhs) const {
        return Dot(rhs);
    }

    Vec3 Vec3::operator*(f32 scalar) const {
        const auto scalarVec = _mm_set1_ps(scalar);
        return Vec3(_mm_mul_ps(m128_f32, scalarVec));
    }

    Vec3& Vec3::operator*=(f32 scalar) {
        const auto scalarVec = _mm_set1_ps(scalar);
        m128_f32             = _mm_mul_ps(m128_f32, scalarVec);
        return *this;
    }

    f32 Vec3::Dot(const Vec3& rhs) const {
        // Multiply vectors
        auto mul = _mm_mul_ps(m128_f32, rhs.m128_f32);
        // Horizontal add to sum the products
        mul = _mm_hadd_ps(mul, mul);  // Add adjacent pairs (X*X + Y*Y, Z*Z + 0)
        mul = _mm_hadd_ps(mul, mul);  // Sum the results (X*X + Y*Y + Z*Z)
        return _mm_cvtss_f32(mul);    // Extract the result as a float
    }

    Vec3 Vec3::Cross(const Vec3& rhs) const {
        // Shuffle elements
        const __m128 lhsYZX =
          _mm_shuffle_ps(m128_f32, m128_f32, _MM_SHUFFLE(3, 0, 2, 1));  // YZX from this
        const __m128 rhsYZX =
          _mm_shuffle_ps(rhs.m128_f32, rhs.m128_f32, _MM_SHUFFLE(3, 0, 2, 1));  // YZX from rhs

        // Multiply lhs and rhs shuffles
        const __m128 mul1 = _mm_mul_ps(m128_f32, rhsYZX);      // X * Z, Y * X, Z * Y
        const __m128 mul2 = _mm_mul_ps(lhsYZX, rhs.m128_f32);  // Z * X, X * Y, Y * Z

        // Subtract to get the cross product components
        __m128 cross = _mm_sub_ps(mul1, mul2);  // (Y*Z - Z*Y), (Z*X - X*Z), (X*Y - Y*X)

        return Vec3(
          _mm_shuffle_ps(cross, cross, _MM_SHUFFLE(3, 0, 2, 1)));  // Shuffle back to X, Y, Z order
    }

    f32 Vec3::Length() const {
        return sqrtf(Dot(*this));
    }

    Vec3 Vec3::Normalize() const {
        const auto length = Length();
        if (length == 0.0f)
            return {0.0f, 0.0f, 0.0f};
        return *this * (1.f / length);
    }
}  // namespace XnMath