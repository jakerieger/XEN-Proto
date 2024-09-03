// Author: Jake Rieger
// Created: 9/2/2024.
//

#pragma once

#include "Shared/Types.h"

struct MenuAction {
    str Name;
    str Shortcut;
    Function<void()> Action;
    bool Separator = false;
};

struct Menu {
    str Name;
    Vector<MenuAction> Actions;
};

class MenuBar {
public:
    explicit MenuBar(const Vector<Menu>& menus);
    void Draw();

private:
    Vector<Menu> mMenus = {};
};
