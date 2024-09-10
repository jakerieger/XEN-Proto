// Author: Jake Rieger
// Created: 9/9/2024.
//

#include "Math.h"
#include "VectorOperations.h"
#include "MatrixOperations.h"

#include <iostream>

int main() {
    if (!XnMath::VerifySupport()) {
        return 1;
    }

    using namespace XnMath;

    const Vec3 v1 = {1, 2, 3};
    const Vec3 v2 = {4, 5, 6};

    const auto dot = Dot(v1, v2);
    std::cout << dot << std::endl;

    const auto cross = Cross(v1, v2);
    std::cout << cross.X << ", " << cross.Y << ", " << cross.Z << std::endl;

    const auto norm = Normalize(v1);
    std::cout << norm.X << ", " << norm.Y << ", " << norm.Z << std::endl;

    const Mat4x4 mat = Mat4x4::Identity();
    std::cout << mat.SlowDeterminant() << std::endl;
    std::cout << mat.FastDeterminant() << std::endl;

    return 0;
}