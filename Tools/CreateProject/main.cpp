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

class CreateProject final : public IApp {
public:
    CreateProject() : IApp("Create Project", kXenTheme, "Data/logo_1x.png") {}

    void DrawGame() override {}

    void Draw(u32 sceneTexture) override {
        ImGui::Begin("Create Project");

        ImGui::End();
    }

    ~CreateProject() override = default;
};

int main() {
    CreateProject project;
    project.Run();
    return 0;
}