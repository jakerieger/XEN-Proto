// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma once

#include "Shared/Types.h"
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

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
    void Quit() const;

    virtual void DrawGame()             = 0;
    virtual void Draw(u32 sceneTexture) = 0;

    template<typename T, typename... Args>
    void CreateWindow(Args&&... args) {
        mWindows.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    void LoadFont(const str& name, const Path& ttfFile, f32 size = 20.f);
    [[nodiscard]] ImFont* GetFont(const str& name) const;

protected:
    void Initialize(const ImVec2& initSize);
    void Shutdown() const;
    [[nodiscard]] static RenderBuffers CreateRenderBuffers(i32 width, i32 height);

    GLFWwindow* mWindow = None;
    str mWindowTitle;
    Path mIconPath;
    Theme mTheme;
    ImVec2 mWindowSize;
    Vector<Unique<IWindow>> mWindows;
    Dictionary<str, ImFont*> mFonts;
};