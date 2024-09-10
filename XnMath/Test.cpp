// Author: Jake Rieger
// Created: 9/9/2024.
//

#include "Math.h"
#include "VectorOperations.h"

#include <iostream>

int main() {
    if (!XnMath::VerifySupport()) {
        return 1;
    }

    using namespace XnMath;

    const Vec3 v1    = {1, 2, 3};
    const Vec3 v2    = {4, 5, 6};
    const auto cross = v1.Cross(v2);
    const auto dot   = v1.Dot(v2);

    std::cout << cross.X << ", " << cross.Y << ", " << cross.Z << std::endl;
    std::cout << dot << std::endl;

    const auto dot2 = Dot(v1, v2);
    std::cout << dot2 << std::endl;

    const auto cross2 = Cross(v1, v2);
    std::cout << cross2.X << ", " << cross2.Y << ", " << cross2.Z << std::endl;

    return 0;
}