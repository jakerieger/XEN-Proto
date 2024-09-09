// Author: Jake Rieger
// Created: 9/8/2024.
//

#pragma warning(disable : 4996)

#include "Tools/XnApp/App.h"
#include "Tools/XnApp/MenuBar.h"
#include "Tools/XnApp/Window.h"
#include "Tools/XnApp/Widgets.h"

#include "Tools/Resources/XenTheme.h"
#include "Tools/Resources/IconsFontAwesome6Pro.h"

#include <Types.h>
#include <imgui/imgui.h>

static constexpr ImWchar icons[] = {ICON_MIN_FA, ICON_MAX_FA, 0};

class CreateProject final : public IApp {
public:
    CreateProject()
        : IApp("Create Project",
               kXenTheme,
               "Data/logo_1x.png",
               ImVec2(600, 300),
               true,
               false,
               false, false) {
        LoadFont("Inter_18", "Data/Fonts/Inter_18pt-Medium.ttf", 18.f);

        ImFontConfig config;
        config.MergeMode        = true;
        config.GlyphMinAdvanceX = 13.f;
        const ImGuiIO& io       = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("Data/Fonts/fa-solid-900.ttf", 13.f, &config, icons);
    }

    void DrawGame() override {}

    void Draw(u32 sceneTexture) override {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::Begin("Create Project",
                     None,
                     ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize);

        // UI
        {
            ImGui::Text("Name: ");
            ImGui::SameLine(100);
            ImGui::InputText("##Name", mNameBuffer, IM_ARRAYSIZE(mNameBuffer));

            ImGui::Text("Location: ");
            ImGui::SameLine(100);
            ImGui::InputText("##Location", mLocationBuffer, IM_ARRAYSIZE(mLocationBuffer));

            ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 220.f);
            Widgets::PrimaryButton("Create", {100, 32}, [this] { ResetState(); });
            ImGui::SameLine();
            Widgets::SecondaryButton("Quit", {100, 32}, [this] {
                ResetState();
                Quit();
            });
        }

        ImGui::End();
        ImGui::PopStyleVar();
    }

    ~CreateProject() override = default;

    void ResetState() {
        mNameBuffer[0]     = '\0';
        mLocationBuffer[0] = '\0';
    }

private:
    char mNameBuffer[64]      = {'\0'};
    char mLocationBuffer[256] = {'\0'};
};

int main() {
    CreateProject project;
    project.Run();
    return 0;
}