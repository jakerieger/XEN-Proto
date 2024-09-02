// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma once

#include <Shared/Types.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

class IApp {
public:
    using Theme = Dictionary<std::string, ImVec4>;

    struct RenderBuffers {
        u32 FrameBuffer  = 0;
        u32 RenderBuffer = 0;
        u32 SceneTexture = 0;
    };

    IApp(const str& title,
         const Theme& theme,
         const Path& icon,
         const ImVec2& initSize = ImVec2(1280, 720));
    virtual ~IApp() = default;

    void Run();
    [[nodiscard]] GLFWwindow* GetWindow() const;

    virtual void Draw(u32 sceneTexture) = 0;

private:
    void Initialize(const ImVec2& initSize);
    void Shutdown() const;
    [[nodiscard]] static RenderBuffers CreateRenderBuffers(i32 width, i32 height);

    GLFWwindow* mWindow = None;
    str mWindowTitle;
    Path mIconPath;
    Theme mTheme;
    ImVec2 mWindowSize;
};