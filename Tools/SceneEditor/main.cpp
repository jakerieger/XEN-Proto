// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma warning(disable : 4996)

#include "Shared/Types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

GLFWwindow* gWindow = None;
int gWidth          = 1280;
int gHeight         = 720;

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

void Initialize() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("Data/Fonts/ChakraPetch-Regular.ttf", 20.f);

    // Define ui theme
    {
        static std::map<std::string, ImVec4> colors {
          {"panel", HexToRGBA(0xFFFFFFFF)},
          {"scene", HexToRGBA(0xFFFFFFFF)},
          {"frame", HexToRGBA(0xFFFFFFFF)},
          {"accent", HexToRGBA(0xFFFFFFFF)},
          {"border", HexToRGBA(0xFFFFFFFF)},
          {"text", HexToRGBA(0xFFFFFFFF)},
          {"text_inactive", HexToRGBA(0xFFFFFFFF)},
          {"button", HexToRGBA(0xFFFFFFFF)},
          {"button_hover", HexToRGBA(0xFFFFFFFF)},
          {"selected", HexToRGBA(0xFFFFFFFF)},
          {"header", HexToRGBA(0xFFFFFFFF)},
          {"menu", HexToRGBA(0xFFFFFFFF)},
          {"success", HexToRGBA(0xFFFFFFFF)},
          {"warning", HexToRGBA(0xFFFFFFFF)},
          {"error", HexToRGBA(0xFFFFFFFF)},
        };

        // Initialize our window style vars
        static float window_rounding = 0.0f;
        static float frame_rounding  = 0.0f;
        static float border_size     = 1.0f;

        ImGuiStyle* style   = &ImGui::GetStyle();
        ImVec4* styleColors = style->Colors;

        style->WindowRounding   = window_rounding;
        style->FrameRounding    = frame_rounding;
        style->WindowBorderSize = border_size;
        style->FrameBorderSize  = border_size;
        style->TabRounding      = frame_rounding;

        styleColors[ImGuiCol_Text]                 = colors["text"];
        styleColors[ImGuiCol_TextDisabled]         = colors["text_inactive"];
        styleColors[ImGuiCol_WindowBg]             = colors["panel"];
        styleColors[ImGuiCol_ChildBg]              = colors["frame"];
        styleColors[ImGuiCol_PopupBg]              = colors["menu"];
        styleColors[ImGuiCol_Border]               = colors["border"];
        styleColors[ImGuiCol_BorderShadow]         = ImVec4(0.f, 0.f, 0.f, 0.f);
        styleColors[ImGuiCol_FrameBg]              = colors["frame"];
        styleColors[ImGuiCol_FrameBgHovered]       = colors["frame"];
        styleColors[ImGuiCol_FrameBgActive]        = colors["frame"];
        styleColors[ImGuiCol_TitleBg]              = colors["panel"];
        styleColors[ImGuiCol_TitleBgActive]        = colors["panel"];
        styleColors[ImGuiCol_TitleBgCollapsed]     = colors["panel"];
        styleColors[ImGuiCol_MenuBarBg]            = colors["menu"];
        styleColors[ImGuiCol_ScrollbarBg]          = colors["panel"];
        styleColors[ImGuiCol_ScrollbarGrab]        = colors["selected"];
        styleColors[ImGuiCol_ScrollbarGrabHovered] = colors["selected"];
        styleColors[ImGuiCol_ScrollbarGrabActive]  = colors["selected"];
        styleColors[ImGuiCol_CheckMark]            = colors["text"];
        styleColors[ImGuiCol_SliderGrab]           = colors["accent"];
        styleColors[ImGuiCol_SliderGrabActive]     = colors["accent"];
        styleColors[ImGuiCol_Button]               = colors["button"];
        styleColors[ImGuiCol_ButtonHovered]        = colors["button_hover"];
        styleColors[ImGuiCol_ButtonActive]         = colors["button_hover"];
        styleColors[ImGuiCol_Header]               = colors["header"];
        styleColors[ImGuiCol_HeaderHovered]        = colors["header"];
        styleColors[ImGuiCol_HeaderActive]         = colors["header"];
        styleColors[ImGuiCol_Separator]            = styleColors[ImGuiCol_Border];
        styleColors[ImGuiCol_SeparatorHovered]     = colors["accent"];
        styleColors[ImGuiCol_SeparatorActive]      = colors["accent"];
        styleColors[ImGuiCol_ResizeGrip]           = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
        styleColors[ImGuiCol_ResizeGripHovered]    = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        styleColors[ImGuiCol_ResizeGripActive]     = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        styleColors[ImGuiCol_Tab]                  = colors["header"];
        styleColors[ImGuiCol_TabHovered]           = colors["selected"];
        styleColors[ImGuiCol_TabActive]            = colors["selected"];
        styleColors[ImGuiCol_TabUnfocused]         = styleColors[ImGuiCol_Tab];
        styleColors[ImGuiCol_TabUnfocusedActive]   = styleColors[ImGuiCol_TabActive];
        styleColors[ImGuiCol_TableBorderLight]     = ImVec4(0.f, 0.f, 0.f, 0.f);
        styleColors[ImGuiCol_TableBorderStrong]    = ImVec4(0.f, 0.f, 0.f, 0.f);
        styleColors[ImGuiCol_PlotLines]            = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        styleColors[ImGuiCol_PlotLinesHovered]     = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        styleColors[ImGuiCol_PlotHistogram]        = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        styleColors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        styleColors[ImGuiCol_TableHeaderBg]        = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        styleColors[ImGuiCol_TableBorderStrong] =
          ImVec4(0.31f, 0.31f, 0.35f, 1.00f);  // Prefer using Alpha=1.0 here
        styleColors[ImGuiCol_TableBorderLight] =
          ImVec4(0.23f, 0.23f, 0.25f, 1.00f);  // Prefer using Alpha=1.0 here
        styleColors[ImGuiCol_TableRowBg]     = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        styleColors[ImGuiCol_TableRowBgAlt]  = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        styleColors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        styleColors[ImGuiCol_DragDropTarget] = colors["accent"];
        styleColors[ImGuiCol_NavHighlight] =
          ImVec4(30.f / 255.f, 30.f / 255.f, 30.f / 255.f, 1.00f);
        styleColors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        styleColors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        styleColors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
    }

    ImGui_ImplGlfw_InitForOpenGL(gWindow, true);
    ImGui_ImplOpenGL3_Init();
}

void Draw() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::SetNextWindowPos(ImVec2(10, 10));

    ImGui::Begin("Debug",
                 nullptr,
                 0 /*ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove*/);
    { ImGui::Text("FPS"); }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    gWindow = glfwCreateWindow(gWidth, gHeight, "XEN Scene Editor", NULL, NULL);
    glfwMakeContextCurrent(gWindow);

    if (!gladLoadGLLoader(RCAST<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        throw RuntimeError("Failed to initialize GLAD");
    }

    glViewport(0, 0, gWidth, gHeight);
    glClearColor(10.f / 255.f, 11.f / 255.f, 16.f / 255.f, 1.0f);

    glfwSwapInterval(1);
    glfwMaximizeWindow(gWindow);

    Initialize();
    while (!glfwWindowShouldClose(gWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        Draw();

        glfwSwapBuffers(gWindow);
    }
    Shutdown();

    glfwDestroyWindow(gWindow);
    glfwTerminate();

    return 0;
}