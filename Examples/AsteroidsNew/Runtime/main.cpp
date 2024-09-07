// Author: Jake Rieger
// Created: 9/5/2024.
//

#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_MAIN int WinMain()
#else
    #define PLATFORM_MAIN int main()
#endif

#include "Shared/Types.h"
#include "Source/Asteroids.h"

#include <cstdio>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLFWwindow* gWindow = None;

PLATFORM_MAIN {
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

    gWindow = glfwCreateWindow(1280, 720, "Asteroids", None, None);
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

    const auto game = new Asteroids();
    game->Initialize(gWindow);

    while (!glfwWindowShouldClose(gWindow)) {
        glfwPollEvents();
        game->RequestFrame();
    }

    game->Shutdown();
    delete game;

    glfwDestroyWindow(gWindow);
    glfwTerminate();

    return 0;
}