// Author: Jake Rieger
// Created: 9/3/2024.
//

#pragma once

#include "Shared/Types.h"
#include <imgui.h>

namespace Widgets {
    void PrimaryButton(const char* text, const ImVec2& size, const Function<void()>& onClick);
    void SecondaryButton(const char* text, const ImVec2& size, const Function<void()>& onClick);
}  // namespace Widgets
