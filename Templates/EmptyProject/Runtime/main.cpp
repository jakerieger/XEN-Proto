// Author: Jake Rieger
// Created: 9/5/2024.
//

#include "Shared/Types.h"
#include "Source/Empty.h"

#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* gWindow = None;

#if defined(_WIN32) || defined(_WIN64)
int WinMain() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW3\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    #ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    #endif

    gWindow = glfwCreateWindow(1280, 720, "Empty", None, None);
    if (!gWindow) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(gWindow);

    if (!gladLoadGLLoader(RCAST<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    const auto empty = new Empty(gWindow);

    while (!glfwWindowShouldClose(gWindow)) {
        glfwPollEvents();

        empty->Render();

        glfwSwapBuffers(gWindow);
    }

    delete empty;

    glfwDestroyWindow(gWindow);
    glfwTerminate();

    return 0;
}
#else
int main() {
    return 0;
}
#endif