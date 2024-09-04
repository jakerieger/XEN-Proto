// Author: Jake Rieger
// Created: 9/3/2024.
//

#include "Widgets.h"
#include "Tools/Resources/XenTheme.h"

namespace Widgets {
    void PrimaryButton(const char* text, const ImVec2& size, const Function<void()>& onClick) {
        ImGui::PushStyleColor(ImGuiCol_Text, HexToRGBA(0xFFFFFFFF));
        ImGui::PushStyleColor(ImGuiCol_Button, kXenTheme["button"]);
        if (ImGui::Button(text, size)) {
            onClick();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
    }

    void SecondaryButton(const char* text, const ImVec2& size, const Function<void()>& onClick) {
        ImGui::PushStyleColor(ImGuiCol_Button, HexToRGBA(0xFF1A1C29));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, HexToRGBA(0xD01a1c29));
        if (ImGui::Button(text, size)) {
            onClick();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
    }
}  // namespace Widgets