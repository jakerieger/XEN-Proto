// Author: Jake Rieger
// Created: 9/5/2024.
//

#pragma once
#define CORE_API __declspec(dllexport)

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "XnCore/Game.h"

class CORE_API Asteroids final : public IGame {
public:
    Asteroids() : IGame("Asteroids") {}
    void Create() override;
    void Destroy() override;
};

extern "C" CORE_API IGame* CreateInstance();

extern "C" CORE_API void DestroyInstance(const IGame* instance);