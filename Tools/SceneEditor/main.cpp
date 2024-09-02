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

void Initialize() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
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