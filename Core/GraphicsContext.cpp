// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "GraphicsContext.h"

#include "PipelineStates.h"

GraphicsContext::GraphicsContext(const Shared<EngineConfig>& config, const str& title)
    : mWidthCreated(0), mHeightCreated(0), mWidthCurrent(0), mHeightCurrent(0), mConfig(config) {
    const auto width      = config->GetRenderingConfig().ResX;
    const auto height     = config->GetRenderingConfig().ResY;
    const auto vsync      = config->GetRenderingConfig().VSync;
    const auto windowMode = config->GetRenderingConfig().WindowMode;

    if (glfwInit() == GLFW_FALSE) {
        throw RuntimeError("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

    // TODO: Handle window modes here, prior to swap interval

    glfwSwapInterval(vsync);

    mWindow = UniqueDelete<GLFWwindow, DestroyWindow>(
      glfwCreateWindow(CAST<int>(width), CAST<int>(height), title.c_str(), None, None));
    if (!mWindow) {
        glfwTerminate();
        throw RuntimeError("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(mWindow.get());

    if (!gladLoadGLLoader(RCAST<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        throw RuntimeError("Failed to initialize GLAD");
    }

    OnResize(width, height);
    glfwSetFramebufferSizeCallback(mWindow.get(), [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });
}

GraphicsContext::~GraphicsContext() {
    glfwDestroyWindow(mWindow.get());
    glfwTerminate();

    mWindow.reset();
}

GLFWwindow* GraphicsContext::GetWindow() const {
    return mWindow.get();
}

void GraphicsContext::BeginFrame() const {
    glfwPollEvents();
    glClearColor(17.f / 255.f, 18.f / 255.f, 28.f / 255.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set default OpenGL states for blend, depth, culling, etc
    // TODO: Make this modular to simplify OpenGL state management and give game devs control over
    // the rendering pipeline
    PipelineStates::SetDefaults();
}

void GraphicsContext::EndFrame() const {
    glfwSwapBuffers(mWindow.get());
}
void GraphicsContext::OnResize(u32 width, u32 height) {
    mWidthCurrent  = width;
    mHeightCurrent = height;
}