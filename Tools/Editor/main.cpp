// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma warning(disable : 4996)

#include "CachedLayout.h"
#include "FileTemplates.h"
#include "Shared/IO.h"
#include "Shared/Types.h"
#include "Tools/XnApp/App.h"
#include "Tools/XnApp/MenuBar.h"
#include "Tools/XnApp/Window.h"
#include "Tools/Resources/XenTheme.h"

#include <iostream>
#include <nfd.h>

struct Project {
    Path RootDir;
    str Name;
    str XenVersion;
};

namespace Windows {
    class NewGameObjectModal final : public IWindow {
    public:
        explicit NewGameObjectModal(const Project& project) : mProject(project) {
            const auto rootDir = project.RootDir.string() + "/Source";
            std::cout << rootDir << std::endl;
            std::strncpy(mPathBuffer, rootDir.c_str(), sizeof(mPathBuffer) - 1);
            mPathBuffer[sizeof(mPathBuffer) - 1] = '\0';
        }

        void Draw(u32 sceneTexture, IApp* app) override {
            ImGui::SetNextWindowSize(ImVec2(800, 280));
            if (ImGui::BeginPopupModal("Create new GameObject",
                                       nullptr,
                                       ImGuiWindowFlags_NoResize)) {
                ImGui::Text("Name: ");
                ImGui::SameLine(100);
                ImGui::InputText("##Name", mNameBuffer, IM_ARRAYSIZE(mNameBuffer));

                ImGui::Text("Path: ");
                ImGui::SameLine(100);
                ImGui::InputText("##Path", mPathBuffer, IM_ARRAYSIZE(mPathBuffer));
                ImGui::SameLine();
                if (ImGui::Button("...", ImVec2(32, 24))) {
                    // Open folder browser dialog or whatever its called
                    nfdchar_t* outPath       = None;
                    const auto startDir      = mProject.RootDir.append("Source");
                    const nfdresult_t result = NFD_PickFolder(startDir.string().c_str(), &outPath);
                    if (result == NFD_OKAY) {
                        std::strncpy(mPathBuffer, outPath, sizeof(mPathBuffer) - 1);
                        mPathBuffer[sizeof(mPathBuffer) - 1] = '\0';
                    }
                }

                const auto headerPath = std::format("{}\\{}.h", mPathBuffer, mNameBuffer);
                const auto sourcePath = std::format("{}\\{}.cpp", mPathBuffer, mNameBuffer);

                ImGui::Text("Traits: ");
                ImGui::SameLine(100);
                ImGui::Checkbox("Drawable", &mDrawable);

                ImGui::Text("");
                ImGui::SameLine(100);
                ImGui::Checkbox("Input Listener", &mInputListener);

                ImGui::Text("");
                ImGui::SameLine(100);
                ImGui::Checkbox("Physics Object", &mPhysicsObject);

                ImGui::Text("Header File: ");
                ImGui::SameLine(100);
                ImGui::TextDisabled("%s", headerPath.c_str());

                ImGui::Text("Source File: ");
                ImGui::SameLine(100);
                ImGui::TextDisabled("%s", sourcePath.c_str());

                ImGui::Spacing();

                ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 220.f);
                if (ImGui::Button("Create", ImVec2(100, 32))) {
                    // IO::Write(sourcePath, "PISS IN MY ASS");
                    // IO::Write(headerPath,
                    //           FileTemplates::GameObjectSourceFile(mNameBuffer,
                    //                                               mDrawable,
                    //                                               mInputListener,
                    //                                               mPhysicsObject));
                    ResetState();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SameLine();

                ImGui::PushStyleColor(ImGuiCol_Button, HexToRGBA(0xFF1A1C29));
                if (ImGui::Button("Cancel", ImVec2(100, 32))) {
                    ResetState();
                    ImGui::CloseCurrentPopup();
                }
                ImGui::PopStyleColor();

                ImGui::EndPopup();
            }
        }

        void ResetState() override {
            mNameBuffer[0] = '\0';
            mDrawable      = false;
            mInputListener = false;
            mPhysicsObject = false;
        }

    private:
        char mNameBuffer[256] = {'\0'};
        char mPathBuffer[256] = {'\0'};
        bool mDrawable        = false;
        bool mInputListener   = false;
        bool mPhysicsObject   = false;

        Project mProject;
    };

    class SceneWindow final : public IWindow {
    public:
        void Draw(u32 sceneTexture, IApp* app) override {
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

        void ResetState() override {}
    };

    class HierarchyWindow final : public IWindow {
    public:
        void Draw(u32 sceneTexture, IApp* app) override {
            ImGui::Begin("Hierarchy");
            ImGui::Text("Hello, world!");
            ImGui::End();
        }

        void ResetState() override {}
    };

    class InspectorWindow final : public IWindow {
    public:
        void Draw(u32 sceneTexture, IApp* app) override {
            ImGui::Begin("Inspector");
            ImGui::Text("Hello, world!");
            ImGui::End();
        }

        void ResetState() override {}
    };

    class AnalyticsWindow final : public IWindow {
    public:
        void Draw(u32 sceneTexture, IApp* app) override {
            ImGui::Begin("Analytics");
            ImGui::Text("Hello, world!");
            ImGui::End();
        }

        void ResetState() override {}
    };
}  // namespace Windows

class Editor final : public IApp {
public:
    Editor() : IApp("XEN Editor", kXenTheme, "Data/logo_1x.png") {
        LoadProject(R"(C:\Users\conta\Code\CPP\2DGameEngine\Templates\Empty\Empty.xenproj)");

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

        CreateWindow<Windows::NewGameObjectModal>(mProject);
        CreateWindow<Windows::SceneWindow>();
        CreateWindow<Windows::HierarchyWindow>();
        CreateWindow<Windows::InspectorWindow>();
        CreateWindow<Windows::AnalyticsWindow>();
    }

    void Draw(u32 sceneTexture) override {
        mMenuBar->Draw();

        for (const auto& window : mWindows) {
            window->Draw(sceneTexture, this);
        }

        ImGui::Begin("Performance");
        ImGui::Text("FPS: %d", (int)ImGui::GetIO().Framerate);
        ImGui::End();
    }

    void LoadProject(const Path& projectPath) {
        mProject            = Project();
        mProject.RootDir    = projectPath.parent_path();  // Don't include project file
        mProject.Name       = projectPath.filename().string();
        mProject.XenVersion = "0.0.1";
    }

    [[nodiscard]] Project& GetProject() {
        return mProject;
    }

    ~Editor() override {
        mMenuBar.reset();
    }

private:
    Unique<MenuBar> mMenuBar;
    Project mProject;
};

int main() {
    Editor editor;
    editor.Run();

    return 0;
}