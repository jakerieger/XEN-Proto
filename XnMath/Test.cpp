// Author: Jake Rieger
// Created: 9/9/2024.
//

#include "Math.h"

#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>

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

    const auto xnOrtho = XnMath::MatrixOrthographic(0.f, 0.f, 10.f, 10.f, -1.f, 1.f);
    auto glmOrtho      = glm::ortho(0.f, 10.f, 10.f, 0.f, -1.f, 1.f);

    std::cout << "XnMath: \n";
    PrintMatrix(xnOrtho);
    std::cout << "\nGLM: \n";
    PrintMatrix(glmOrtho);

    return 0;
}