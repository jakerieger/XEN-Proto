// Author: Jake Rieger
// Created: 9/8/2024.
//

#pragma once

#include "XnCore/Game.h"

#include <Types.h>
#include <GLFW/glfw3.h>

// Function pointer typedefs
typedef void (*InitializeFunc)(GLFWwindow*);
typedef void (*ShutdownFunc)();
typedef void (*RequestFrameFunc)();

typedef IGame* (*CreateGameFunc)();
typedef void (*DestroyGameFunc)(const IGame*);

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>

static bool LoadGameProcess(const char* gameProc,
                            HMODULE& module,
                            CreateGameFunc& createFunc,
                            DestroyGameFunc& destroyFunc) {
    const auto hModule = LoadLibrary(gameProc);
    if (!hModule) {
        MessageBox(None, "Error loading Core.dll", "Error", MB_OK);
        return false;
    }

    // Get function pointers
    const auto pCreateGameFunc = (CreateGameFunc)GetProcAddress(hModule, "CreateInstance");
    if (!pCreateGameFunc) {
        MessageBox(None, "Error getting CreateInstance function handle", "Error", MB_OK);
        FreeLibrary(hModule);
        return false;
    }

    const auto pDestroyInstanceFunc = (DestroyGameFunc)GetProcAddress(hModule, "DestroyInstance");
    if (!pDestroyInstanceFunc) {
        MessageBox(None, "Error getting DestroyInstance function handle", "Error", MB_OK);
        FreeLibrary(hModule);
        return false;
    }

    module      = hModule;
    createFunc  = pCreateGameFunc;
    destroyFunc = pDestroyInstanceFunc;

    std::cout << "Created GameProcess : " << gameProc << std::endl;

    return true;
}

static bool UnloadGameProcess(HMODULE module) {
    return FreeLibrary(module);
}

    #ifdef CreateWindow
        #undef CreateWindow
    #endif
    #ifdef DestroyWindow
        #undef DestroyWindow
    #endif

#endif