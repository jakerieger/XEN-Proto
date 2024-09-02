// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma warning(disable : 4996)

#include "Shared/Types.h"
#include "Tools/ImguiApp.h"

#include <imgui_internal.h>
#include <nfd.h>

ImVec4 HexToRGBA(const u32 hex) {
    const unsigned char alphaByte = (hex >> 24) & 0xFF;
    const unsigned char redByte   = (hex >> 16) & 0xFF;
    const unsigned char greenByte = (hex >> 8) & 0xFF;
    const unsigned char blueByte  = hex & 0xFF;

    auto a = static_cast<float>(static_cast<u32>(alphaByte) / 255.0);
    auto r = static_cast<float>(static_cast<u32>(redByte) / 255.0);
    auto g = static_cast<float>(static_cast<u32>(greenByte) / 255.0);
    auto b = static_cast<float>(static_cast<u32>(blueByte) / 255.0);

    return {r, g, b, a};
}

static Dictionary<std::string, ImVec4> gTheme {{"panel", HexToRGBA(0xFF161722)},
                                               {"scene", HexToRGBA(0xFFFFFFFF)},
                                               {"frame", HexToRGBA(0xFF0a0b10)},
                                               {"accent", HexToRGBA(0xFF8957e5)},
                                               {"border", HexToRGBA(0xFF0A0B10)},
                                               {"text", HexToRGBA(0xFFc0caf5)},
                                               {"text_inactive", HexToRGBA(0xFF414868)},
                                               {"button", HexToRGBA(0xFF8957e5)},
                                               {"button_hover", HexToRGBA(0xF08957e5)},
                                               {"selected", HexToRGBA(0xFF101118)},
                                               {"header", HexToRGBA(0xFF1a1b26)},
                                               {"menu", HexToRGBA(0xFF0A0B10)},
                                               {"success", HexToRGBA(0xFF73daca)},
                                               {"warning", HexToRGBA(0xFFff9e64)},
                                               {"error", HexToRGBA(0xFFFF3366)},
                                               {"separator", HexToRGBA(0xFF24283b)}};

namespace Windows {
    void MenuBar(ImguiApp* app) {
        constexpr ImGuiWindowFlags window_flags =
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        str menuAction;
        if (ImGui::BeginViewportSideBar("##toolbar",
                                        ImGui::GetMainViewport(),
                                        ImGuiDir_Up,
                                        ImGui::GetFrameHeight(),
                                        window_flags)) {
            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("New Scene", "Ctrl+N")) {
                    }
                    if (ImGui::MenuItem("Open Scene", "Ctrl+O")) {
                        nfdchar_t* outPath       = None;
                        const nfdresult_t result = NFD_OpenDialog(None, None, &outPath);
                        if (result == NFD_OKAY) {
                            free(outPath);
                        }
                    }
                    if (ImGui::MenuItem("Save Scene", "Ctrl+S")) {
                        nfdchar_t* savePath = None;
                        nfdresult_t result  = NFD_SaveDialog(None, None, &savePath);
                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Export to engine", "Ctrl+E")) {
                        menuAction = "Export";
                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
                        glfwSetWindowShouldClose(app->GetWindow(), true);
                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            ImGui::End();
        }
        ImGui::PopStyleVar();

        if (menuAction == "Export") {
            ImGui::OpenPopup("Export");
        }

        if (ImGui::BeginPopupModal("Export")) {
            ImGui::Text("Export to engine");
            if (ImGui::Button("Cancel")) {
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Button("Export")) {
                // DO export stuff
            }
            ImGui::EndPopup();
        }
    }

    void Scene(u32 sceneTexture) {
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

    void Hierarchy() {
        ImGui::Begin("Hierarchy");
        ImGui::Text("Hello, world!");
        ImGui::End();
    }

    void Settings() {
        ImGui::Begin("Settings");
        ImGui::Text("Hello, world!");
        ImGui::End();
    }

    void Analytics() {
        ImGui::Begin("Analytics");
        ImGui::Text("Hello, world!");
        ImGui::End();
    }
}  // namespace Windows

class Editor final : public ImguiApp {
public:
    Editor() : ImguiApp("XEN Editor", gTheme, "Data/logo_1x.png") {}

    void Draw(u32 sceneTexture) override {
        Windows::MenuBar(this);
        Windows::Scene(sceneTexture);
        Windows::Analytics();
        Windows::Hierarchy();
        Windows::Settings();
    }
};

int main() {
    Editor editor;
    editor.Run();

    return 0;
}