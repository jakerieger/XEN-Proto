// Author: Jake Rieger
// Created: 9/9/2024.
//

#include "Math.h"

#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

void PrintMatrix(const XnMath::Mat4x4& mat) {
    for (int i = 0; i < 4; ++i) {
        std::cout << "[ ";

        float row[4];
        _mm_storeu_ps(row, mat.Rows[i]);
        for (int j = 0; j < 4; ++j) {
            std::cout << row[j] << " ";
        }

        std::cout << "]\n";
    }
}

void PrintMatrix(const glm::mat4& mat) {
    for (int i = 0; i < 4; ++i) {
        std::cout << "[ ";

        for (int j = 0; j < 4; ++j) {
            std::cout << mat[i][j] << " ";
        }

        std::cout << "]\n";
    }
}

int main() {
    if (!XnMath::VerifySupport()) {
        return 1;
    }

    const auto xnOrtho = XnMath::MatrixOrthographic(0.f, 0.f, 1280.f, 720.f, -1.f, 1.f);
    auto glmOrtho      = glm::ortho(0.f, 1280.f, 720.f, 0.f, -1.f, 1.f);

    // std::cout << "XnMath: \n";
    // PrintMatrix(xnOrtho);
    // std::cout << "\nGLM: \n";
    // PrintMatrix(glmOrtho);
    //
    // std::cout << '\n';

    auto xnTranslated  = XnMath::MatrixTranslate(xnOrtho, 0.f, 0.f, -5.f);
    auto glmTranslated = glm::translate(glmOrtho, {0.f, 0.f, -5.f});

    std::cout << "XnMath: \n";
    PrintMatrix(xnTranslated);
    std::cout << "\nGLM: \n";
    PrintMatrix(glmTranslated);

    std::cout << '\n';

    XnMath::Mat4x4 mat1 = XnMath::MatrixIdentity();
    mat1.Rows[0]        = _mm_setr_ps(2.f, 0.f, 0.f, 0.f);
    mat1.Rows[1]        = _mm_setr_ps(0.f, 2.f, 0.f, 0.f);
    mat1.Rows[2]        = _mm_setr_ps(0.f, 0.f, 2.f, 0.f);
    mat1.Rows[3]        = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);
    auto xnScaled       = xnOrtho * mat1;  // XnMath::MatrixScale(xnOrtho, 2.f, 2.f, 2.f);
    auto glmScaled      = glm::scale(glmOrtho, {2.f, 2.f, 2.f});

    std::cout << "XnMath: \n";
    PrintMatrix(xnScaled);
    std::cout << "\nGLM: \n";
    PrintMatrix(glmScaled);

    //
    // std::cout << XnMath::ToDegrees(XnMath::kPi) << "\n";
    // std::cout << XnMath::ToRadians(180.f) << "\n";

    return 0;
}