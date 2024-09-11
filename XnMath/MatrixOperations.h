// Author: Jake Rieger
// Created: 9/9/2024.
//

#pragma once

#include "Mat4x4.h"

namespace XnMath {
    /// @brief Returns a 4x4 identity matrix.
    inline Mat4x4 MatrixIdentity() {
        return Mat4x4::Identity();
    }

    /// @brief Translates a given matrix by vector (x,y,z).
    inline Mat4x4 MatrixTranslate(const Mat4x4& mat, f32 x, f32 y, f32 z) {
        const Mat4x4 translation(_mm_setr_ps(1, 0, 0, 0),
                                 _mm_setr_ps(0, 1, 0, 0),
                                 _mm_setr_ps(0, 0, 1, 0),
                                 _mm_setr_ps(x, y, z, 1));
        return translation * mat;
    }

    /// @brief Scales a given matrix by vector (x,y,z).
    inline Mat4x4 MatrixScale(const Mat4x4& mat, f32 x, f32 y, f32 z) {
        const Mat4x4 scale(_mm_setr_ps(x, 0, 0, 0),
                           _mm_setr_ps(0, y, 0, 0),
                           _mm_setr_ps(0, 0, z, 0),
                           _mm_setr_ps(0, 0, 0, 1));
        return scale * mat;
    }

    /// @brief Rotates a given matrix along its x-axis by <angle> degrees.
    inline Mat4x4 MatrixRotateX(const Mat4x4& mat, f32 angle) {
        const f32 c = std::cos(angle);
        const f32 s = std::sin(angle);
        const Mat4x4 rotateX(_mm_set_ps(0, 0, 0, 1),
                             _mm_set_ps(0, c, -s, 0),
                             _mm_set_ps(0, s, c, 0),
                             _mm_set_ps(0, 0, 0, 1));

        return rotateX * mat;
    }

    /// @brief Rotates a given matrix along its y-axis by <angle> degrees.
    inline Mat4x4 MatrixRotateY(const Mat4x4& mat, f32 angle) {
        const f32 c = std::cos(angle);
        const f32 s = std::sin(angle);
        const Mat4x4 rotateY(_mm_set_ps(0, 0, s, 0),
                             _mm_set_ps(0, 1, 0, 0),
                             _mm_set_ps(0, -s, c, 0),
                             _mm_set_ps(0, 0, 0, 1));

        return rotateY * mat;
    }

    /// @brief Rotates a given matrix along its z-axis by <angle> degrees.
    inline Mat4x4 MatrixRotateZ(const Mat4x4& mat, f32 angle) {
        const f32 c = std::cos(angle);
        const f32 s = std::sin(angle);
        const Mat4x4 rotateZ(_mm_set_ps(0, -s, 0, 0),
                             _mm_set_ps(s, c, 0, 0),
                             _mm_set_ps(0, 0, 1, 0),
                             _mm_set_ps(0, 0, 0, 1));

        return rotateZ * mat;
    }

    /// @brief Returns an orthographic projection matrix, typically used for cameras.
    inline Mat4x4 MatrixOrthographic(f32 left, f32 top, f32 right, f32 bottom, f32 near, f32 far) {
        Mat4x4 ortho = MatrixIdentity();

        ortho.M[0][0] = 2 / (right - left);
        ortho.M[1][1] = 2 / (top - bottom);
        ortho.M[2][2] = 1 / (far - near);
        ortho.M[3][0] = -(right + left) / (right - left);
        ortho.M[3][1] = -(top + bottom) / (top - bottom);
        ortho.M[3][2] = -(near) / (far - near);

        return ortho;
    }
}  // namespace XnMath
