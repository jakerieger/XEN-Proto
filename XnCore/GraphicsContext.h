// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Config.h"
#include "EventSystem.h"
#include "Shared/Types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GraphicsContext {
public:
    GraphicsContext(GLFWwindow* context,
                    const Shared<Config>& config,
                    const str& title,
                    const Shared<EventDispatcher>& dispatcher);
    ~GraphicsContext();
    [[nodiscard]] GLFWwindow* GetWindow() const;

    void BeginFrame() const;
    void EndFrame() const;

    void SetWindowIcon(const Path& icon) const;
    void SetWindowMode(EWindowMode mode) const;
    void SetWindowTitle(const str& title) const;
    void SetResolution(int width, int height);
    void GetResolution(int& width, int& height) const;

    static void SetVSyncEnabled(bool enable);

private:
    struct DestroyWindow {
        void operator()(GLFWwindow* window) const noexcept {
            glfwDestroyWindow(window);
        }
    };

    GLFWwindow* mWindow;
    u32 mWidthCreated, mHeightCreated;
    u32 mWidthCurrent, mHeightCurrent;
    Weak<Config> mConfig;
    Shared<EventDispatcher> mDispatcher;

    void OnResize(u32 width, u32 height);
};