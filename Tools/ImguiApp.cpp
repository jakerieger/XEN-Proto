// Author: Jake Rieger
// Created: 9/1/2024.
//

#include "ImguiApp.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stb_image.h>

ImguiApp::ImguiApp(const str& title, const Theme& theme, const Path& icon, const ImVec2& initSize) {
    mWindowTitle = title;
    mTheme       = theme;
    mIconPath    = icon;
    mWindowSize  = initSize;
}

void ImguiApp::Run() {
    Initialize(mWindowSize);

    const auto buffers = CreateRenderBuffers(CAST<int>(mWindowSize.x), CAST<int>(mWindowSize.y));
    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();

        glBindFramebuffer(GL_FRAMEBUFFER, buffers.FrameBuffer);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render scene

        // Render UI
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDisable(GL_DEPTH_TEST);
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID,
                                         ImGui::GetMainViewport(),
                                         ImGuiDockNodeFlags_PassthruCentralNode);

            Draw(buffers.SceneTexture);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        glfwSwapBuffers(mWindow);
    }

    Shutdown();
}

GLFWwindow* ImguiApp::GetWindow() const {
    return mWindow;
}

ImguiApp::RenderBuffers ImguiApp::CreateRenderBuffers(i32 width, i32 height) {
    u32 frameBuffer;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    u32 sceneTexture;
    glGenTextures(1, &sceneTexture);
    glBindTexture(GL_TEXTURE_2D, sceneTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, None);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, sceneTexture, 0);

    u32 renderBuffer;
    glGenRenderbuffers(1, &renderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_STENCIL_ATTACHMENT,
                              GL_RENDERBUFFER,
                              renderBuffer);

    return {frameBuffer, renderBuffer, sceneTexture};
}

void ImguiApp::Initialize(const ImVec2& initSize) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(CAST<int>(initSize.x),
                               CAST<int>(initSize.y),
                               mWindowTitle.c_str(),
                               None,
                               None);
    glfwMakeContextCurrent(mWindow);

    // Set window icon
    {
        int width, height, numChannels;
        u8* img = stbi_load(mIconPath.string().c_str(), &width, &height, &numChannels, 0);
        if (!img)
            throw RuntimeError("Failed to load icon");

        GLFWimage icons[1];
        icons[0].pixels = img;
        icons->width    = width;
        icons->height   = height;
        glfwSetWindowIcon(mWindow, 1, icons);
        stbi_image_free(img);
    }

    if (!gladLoadGLLoader(RCAST<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        throw RuntimeError("Failed to initialize GLAD");
    }

    glViewport(0, 0, CAST<int>(initSize.x), CAST<int>(initSize.y));
    glClearColor(100.f / 255.f, 110.f / 255.f, 160.f / 255.f, 1.0f);

    glfwSwapInterval(1);
    glfwMaximizeWindow(mWindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;
    io.Fonts->AddFontFromFileTTF("Data/Fonts/ChakraPetch-Regular.ttf", 18.f);

    // Define ui theme
    {
        // Initialize our window style vars
        static float window_rounding = 0.0f;
        static float frame_rounding  = 4.0f;
        static float border_size     = 2.0f;

        ImGuiStyle* style   = &ImGui::GetStyle();
        ImVec4* styleColors = style->Colors;

        style->WindowRounding   = window_rounding;
        style->FrameRounding    = frame_rounding;
        style->WindowBorderSize = border_size;
        style->FrameBorderSize  = border_size;
        style->TabRounding      = frame_rounding;

        styleColors[ImGuiCol_Text]                 = mTheme["text"];
        styleColors[ImGuiCol_TextDisabled]         = mTheme["text_inactive"];
        styleColors[ImGuiCol_WindowBg]             = mTheme["panel"];
        styleColors[ImGuiCol_ChildBg]              = mTheme["frame"];
        styleColors[ImGuiCol_PopupBg]              = mTheme["menu"];
        styleColors[ImGuiCol_Border]               = mTheme["border"];
        styleColors[ImGuiCol_BorderShadow]         = ImVec4(0.f, 0.f, 0.f, 0.f);
        styleColors[ImGuiCol_FrameBg]              = mTheme["frame"];
        styleColors[ImGuiCol_FrameBgHovered]       = mTheme["frame"];
        styleColors[ImGuiCol_FrameBgActive]        = mTheme["frame"];
        styleColors[ImGuiCol_TitleBg]              = mTheme["panel"];
        styleColors[ImGuiCol_TitleBgActive]        = mTheme["panel"];
        styleColors[ImGuiCol_TitleBgCollapsed]     = mTheme["panel"];
        styleColors[ImGuiCol_MenuBarBg]            = mTheme["menu"];
        styleColors[ImGuiCol_ScrollbarBg]          = mTheme["panel"];
        styleColors[ImGuiCol_ScrollbarGrab]        = mTheme["selected"];
        styleColors[ImGuiCol_ScrollbarGrabHovered] = mTheme["selected"];
        styleColors[ImGuiCol_ScrollbarGrabActive]  = mTheme["selected"];
        styleColors[ImGuiCol_CheckMark]            = mTheme["text"];
        styleColors[ImGuiCol_SliderGrab]           = mTheme["accent"];
        styleColors[ImGuiCol_SliderGrabActive]     = mTheme["accent"];
        styleColors[ImGuiCol_Button]               = mTheme["button"];
        styleColors[ImGuiCol_ButtonHovered]        = mTheme["button_hover"];
        styleColors[ImGuiCol_ButtonActive]         = mTheme["button_hover"];
        styleColors[ImGuiCol_Header]               = mTheme["header"];
        styleColors[ImGuiCol_HeaderHovered]        = mTheme["header"];
        styleColors[ImGuiCol_HeaderActive]         = mTheme["header"];
        styleColors[ImGuiCol_Separator]            = mTheme["separator"];
        styleColors[ImGuiCol_SeparatorHovered]     = mTheme["accent"];
        styleColors[ImGuiCol_SeparatorActive]      = mTheme["accent"];
        styleColors[ImGuiCol_ResizeGrip]           = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
        styleColors[ImGuiCol_ResizeGripHovered]    = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
        styleColors[ImGuiCol_ResizeGripActive]     = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
        styleColors[ImGuiCol_Tab]                  = mTheme["header"];
        styleColors[ImGuiCol_TabHovered]           = mTheme["selected"];
        styleColors[ImGuiCol_TabActive]            = mTheme["selected"];
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
        styleColors[ImGuiCol_DragDropTarget] = mTheme["accent"];
        styleColors[ImGuiCol_NavHighlight] =
          ImVec4(30.f / 255.f, 30.f / 255.f, 30.f / 255.f, 1.00f);
        styleColors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        styleColors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        styleColors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.00f, 0.00f, 0.00f, 0.0f);
    }

    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    ImGui_ImplOpenGL3_Init();
}

void ImguiApp::Shutdown() const {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}