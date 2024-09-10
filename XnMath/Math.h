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
}  // namespace XnMath
