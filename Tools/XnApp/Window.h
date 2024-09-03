// Author: Jake Rieger
// Created: 9/3/2024.
//

#pragma once

#include "Shared/Types.h"

class IWindow {
public:
    virtual ~IWindow()                  = default;
    virtual void Draw(u32 sceneTexture) = 0;
};
