// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma warning(disable : 4996)

#include "Shared/Types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* gWindow = None;
int gWidth          = 1280;
int gHeight         = 720;

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

    while (!glfwWindowShouldClose(gWindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(gWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(gWindow);
    glfwTerminate();

    return 0;
}