// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "Shared/Types.h"
#include <array>

namespace Primitives {
    static constexpr std::array<f32, 16> Quad = {
      -1.0f,
      1.0f,
      0.0f,
      1.0f,
      -1.0f,
      -1.0f,
      0.0f,
      0.0f,
      1.0f,
      1.0f,
      1.0f,
      1.0f,
      1.0f,
      -1.0f,
      1.0f,
      0.0f,
    };
}