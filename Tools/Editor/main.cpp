// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma warning(disable : 4996)

#include "Shared/Types.h"
#include "Tools/XnApp/App.h"
#include "Tools/XnApp/MenuBar.h"
#include "Tools/XnApp/Window.h"
#include "Tools/Resources/XenTheme.h"

#include <nfd.h>

namespace Windows {
    class NewGameObjectModal final : public IWindow {
    public:
        void Draw(u32 sceneTexture) override {
            if (ImGui::BeginPopupModal("Create new GameObject")) {
                ImGui::InputText("##Name", mNameBuffer, IM_ARRAYSIZE(mNameBuffer));
                ImGui::EndPopup();
            }
        }

    private:
        char mNameBuffer[256] = {'\0'};
    };

    class SceneWindow final : public IWindow {
    public:
        void Draw(u32 sceneTexture) override {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Scene");
            ImGui::BeginChild("SceneTexture");
            const ImVec2 viewportSize = ImGui::GetWindowSize();

// Ignore this warning ''type cast': conversion from 'unsigned int' to 'void *' of greater size'
// ImGui uses void* to represent generic types, so we can just cast our texture id to void*
#pragma warning(suppress : 4312)
            ImGui::Image((void*)sceneTexture, viewportSize, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::EndChild();
            ImGui::End();
            ImGui::PopStyleVar();
        }
    };

    class HierarchyWindow final : public IWindow {
    public:
        void Draw(u32 sceneTexture) override {
            ImGui::Begin("Hierarchy");
            ImGui::Text("Hello, world!");
            ImGui::End();
        }
    };

    class InspectorWindow final : public IWindow {
    public:
        void Draw(u32 sceneTexture) override {
            ImGui::Begin("Inspector");
            ImGui::Text("Hello, world!");
            ImGui::End();
        }
    };

    class AnalyticsWindow final : public IWindow {
    public:
        void Draw(u32 sceneTexture) override {
            ImGui::Begin("Analytics");
            ImGui::Text("Hello, world!");
            ImGui::End();
        }
    };
}  // namespace Windows

class Editor final : public IApp {
public:
    Editor() : IApp("XEN Editor", kXenTheme, "Data/logo_1x.png") {
        const Menu fileMenu = {"File",
                               {{
                                  "New Scene",
                                  "Ctrl+N",
                                  [] {},
                                },
                                {
                                  "Open Scene",
                                  "Ctrl+O",
                                  [] {},
                                },
                                {
                                  "Save Scene",
                                  "Ctrl+S",
                                  [] {},
                                },
                                {
                                  "Save Scene As",
                                  "Ctrl+Shift+S",
                                  [] {},
                                  true,
                                },
                                {
                                  "New Project",
                                  "Ctrl+Alt+N",
                                  [] {},
                                },
                                {
                                  "Open Project",
                                  "Ctrl+Alt+O",
                                  [] {},
                                },
                                {
                                  "Save Project",
                                  "Ctrl+Alt+S",
                                  [] {},
                                  true,
                                },
                                {
                                  "Open C++ Project",
                                  "",
                                  [] {},
                                },
                                {
                                  "Build All",
                                  "Ctrl+B",
                                  [] {},
                                },
                                {
                                  "Build and Run",
                                  "Ctrl+Shift+B",
                                  [] {},
                                  true,
                                },
                                {
                                  "Exit",
                                  "Ctrl+Q",
                                  [this] { Quit(); },
                                }}};

        const Menu editMenu = {"Edit",
                               {{
                                  "Undo",
                                  "Ctrl+Z",
                                  [] {},
                                },
                                {
                                  "Redo",
                                  "Ctrl+Y",
                                  [] {},
                                },
                                {
                                  "Select All",
                                  "Ctrl+A",
                                  [] {},
                                },
                                {
                                  "Deselect All",
                                  "Shift+D",
                                  [] {},
                                  true,
                                },
                                {
                                  "Project Settings...",
                                  "Ctrl+Alt+N",
                                  [] {},
                                },
                                {
                                  "Editor Preferences...",
                                  "Ctrl+Alt+O",
                                  [] {},
                                }}};

        const Menu createMenu = {"Create",
                                 {{
                                    "GameObject...",
                                    "Ctrl+Shift+G",
                                    [] { ImGui::OpenPopup("Create new GameObject"); },
                                  },
                                  {
                                    "Component...",
                                    "Ctrl+Shift+F",
                                    [] {},
                                  },
                                  {
                                    "Camera...",
                                    "Ctrl+Shift+D",
                                    [] {},
                                    true,
                                  },
                                  {
                                    "Import Asset",
                                    "Shift+I",
                                    [] {},
                                  }}};

        Vector<Menu> menus = {fileMenu, editMenu, createMenu};
        mMenuBar           = std::make_unique<MenuBar>(menus);

        CreateWindow<Windows::NewGameObjectModal>();
        CreateWindow<Windows::SceneWindow>();
        CreateWindow<Windows::HierarchyWindow>();
        CreateWindow<Windows::InspectorWindow>();
        CreateWindow<Windows::AnalyticsWindow>();
    }

    void Draw(u32 sceneTexture) override {
        mMenuBar->Draw();

        for (const auto& window : mWindows) {
            window->Draw(sceneTexture);
        }

        ImGui::Begin("Performance");
        ImGui::Text("FPS: %d", (int)ImGui::GetIO().Framerate);
        ImGui::End();
    }

    ~Editor() override {
        mMenuBar.reset();
    }

private:
    Unique<MenuBar> mMenuBar;
};

int main() {
    Editor editor;
    editor.Run();

    return 0;
}