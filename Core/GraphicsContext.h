// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "EngineConfig.h"
#include "Shared/Types.h"
#include "Shared/glad/glad.h"

#include <GLFW/glfw3.h>

class GraphicsContext {
public:
    GraphicsContext(const Shared<EngineConfig>& config, const str& title);
    ~GraphicsContext();
    [[nodiscard]] GLFWwindow* GetWindow() const;

    void BeginFrame() const;
    void EndFrame() const;

private:
    void FramebufferCallback(GLFWwindow* window, int width, int height);

    struct DestroyWindow {
        void operator()(GLFWwindow* window) const noexcept {
            glfwDestroyWindow(window);
        }
    };

    UniqueDelete<GLFWwindow, DestroyWindow> mWindow;
    u32 mWidthCreated, mHeightCreated;
    u32 mWidthCurrent, mHeightCurrent;
    Shared<EngineConfig> mConfig;
};
