// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Config.h"
#include "Shared/Types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GraphicsContext {
public:
    GraphicsContext(const Shared<Config>& config, const str& title);
    ~GraphicsContext();
    [[nodiscard]] GLFWwindow* GetWindow() const;
    void SetWindowIcon(const Path& icon) const;

    void BeginFrame() const;
    void EndFrame() const;

private:
    struct DestroyWindow {
        void operator()(GLFWwindow* window) const noexcept {
            glfwDestroyWindow(window);
        }
    };

    UniqueDelete<GLFWwindow, DestroyWindow> mWindow;
    u32 mWidthCreated, mHeightCreated;
    u32 mWidthCurrent, mHeightCurrent;
    Weak<Config> mConfig;

    void OnResize(u32 width, u32 height);
};