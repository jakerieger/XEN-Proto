// Author: Jake Rieger
// Created: 9/3/2024.
//

#pragma once

#include "Shared/Types.h"

class IApp;

class IWindow {
public:
    virtual ~IWindow()                             = default;
    virtual void Draw(u32 sceneTexture, IApp* app) = 0;
    virtual void ResetState()                      = 0;
};
