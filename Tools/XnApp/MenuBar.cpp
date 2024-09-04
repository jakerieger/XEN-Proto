// Author: Jake Rieger
// Created: 9/2/2024.
//

#include "MenuBar.h"

#include "Tools/Resources/XenTheme.h"

#include <imgui.h>
#include <imgui_internal.h>

MenuBar::MenuBar(const Vector<Menu>& menus) {
    mMenus = menus;

    for (auto& menu : mMenus) {
        for (auto& action : menu.Actions) {
            mActions[action.Name] = action.Action;
        }
    }
}

void MenuBar::Draw() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, HexToRGBA(0xFF161722));
    if (ImGui::BeginMainMenuBar()) {
        for (auto& [menuName, menuActions] : mMenus) {
            if (ImGui::BeginMenu(menuName.c_str())) {
                for (auto& [itemName, itemShortcut, itemAction, itemSeparated] : menuActions) {
                    if (ImGui::MenuItem(itemName.c_str(), itemShortcut.c_str())) {
                        mCurrentAction = itemName;
                    }

                    if (itemSeparated) {
                        ImGui::Separator();
                    }
                }

                ImGui::EndMenu();
            }
        }

        ImGui::EndMainMenuBar();
    }
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();

    // Call the selected action from the menu
    const auto it = mActions.find(mCurrentAction);
    if (it != mActions.end()) {
        it->second();
    }
    mCurrentAction = "";
}