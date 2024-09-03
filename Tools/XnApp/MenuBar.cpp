// Author: Jake Rieger
// Created: 9/2/2024.
//

#include "MenuBar.h"

#include <imgui.h>
#include <imgui_internal.h>

MenuBar::MenuBar(const Vector<Menu>& menus) {
    mMenus = menus;
}

void MenuBar::Draw() {
    constexpr ImGuiWindowFlags window_flags =
      ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    if (ImGui::BeginViewportSideBar("##toolbar",
                                    ImGui::GetMainViewport(),
                                    ImGuiDir_Up,
                                    ImGui::GetFrameHeight(),
                                    window_flags)) {
        if (ImGui::BeginMenuBar()) {
            for (auto& [menuName, menuActions] : mMenus) {
                if (ImGui::BeginMenu(menuName.c_str())) {
                    for (auto& [itemName, itemShortcut, itemAction, itemSeparated] : menuActions) {
                        if (ImGui::MenuItem(itemName.c_str(), itemShortcut.c_str())) {
                            itemAction();
                        }

                        if (itemSeparated) {
                            ImGui::Separator();
                        }
                    }

                    ImGui::EndMenu();
                }
            }

            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

    ImGui::PopStyleVar();
}