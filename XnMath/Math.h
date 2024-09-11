// Author: Jake Rieger
// Created: 9/9/2024.
//

#pragma once

#pragma region Includes
#include "VectorOperations.h"
#include "MatrixOperations.h"
#pragma endregion

/// @brief SIMD-optimized linear algebra library. Provides utilities for working with
/// vectors and matrices.
///
/// @note XnMath is part of and intended to  be used with XEN Engine. It makes some assumptions
/// about handedness and matrix formats defined below and disallows flexibility in that regard:
///   - Left handed
///   - Row major
namespace XnMath {
    /// @brief XnMath uses SIMD intrinsics to optimize the calculations as much as possible. This
    /// function checks CPU and OS support for SSE and AVX.
    ///
    /// @warning If this returns false, XnMath cannot be used.
    bool VerifySupport();

#pragma region Constants
    static constexpr f32 kPi        = 3.14159265358979323846f;
    static constexpr f32 kPiSqr     = kPi * kPi;
    static constexpr f32 kHalfPi    = kPi * 0.5f;
    static constexpr f32 kThirdPi   = kPi / 3.f;
    static constexpr f32 kTwoPi     = kPi * 2.f;
    static constexpr f32 kTau       = kTwoPi;
    static constexpr f32 kRootTwo   = 1.41421356237309504880f;
    static constexpr f32 kRootThree = 1.73205080756887729352f;
#pragma endregion

    f32 ToDegrees(f32 angle);
    f32 ToRadians(f32 angle);
}  // namespace XnMath
