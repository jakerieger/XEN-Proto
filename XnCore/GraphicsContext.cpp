// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "GraphicsContext.h"

#include "Events.h"
#include "PipelineStates.h"

#include <stb_image.h>

GraphicsContext::GraphicsContext(const Shared<Config>& config,
                                 const str& title,
                                 const Shared<EventDispatcher>& dispatcher)
    : mWidthCreated(0), mHeightCreated(0), mWidthCurrent(0), mHeightCurrent(0), mConfig(config),
      mDispatcher(dispatcher) {
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

    glfwSwapInterval(vsync);
    SetWindowMode(EWindowMode::Windowed /*windowMode*/);
}

GraphicsContext::~GraphicsContext() {
    glfwDestroyWindow(mWindow.get());
    glfwTerminate();

    mWindow.reset();
}

GLFWwindow* GraphicsContext::GetWindow() const {
    return mWindow.get();
}

void GraphicsContext::SetWindowIcon(const Path& icon) const {
    int width, height, numChannels;
    u8* img = stbi_load(icon.string().c_str(), &width, &height, &numChannels, 0);
    if (!img)
        return;

    GLFWimage icons[1];
    icons[0].pixels = img;
    icons->width    = width;
    icons->height   = height;
    glfwSetWindowIcon(GetWindow(), 1, icons);
    stbi_image_free(img);
}

// Function to set the window mode to Windowed
void SetWindowedMode(GLFWwindow* window, int width, int height) {
    // Restore windowed mode by setting the window size
    glfwSetWindowMonitor(window, nullptr, 0, 0, width, height, GLFW_DONT_CARE);
}

// Function to set the window mode to Borderless Fullscreen
void SetBorderlessFullscreenMode(GLFWwindow* window) {
    // Get the current monitor
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (monitor == nullptr)
        return;

    // Get the monitor's video mode
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (mode == nullptr)
        return;

    // Set the window to fullscreen mode with no borders
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
}

// Function to set the window mode to Fullscreen
void SetFullscreenMode(GLFWwindow* window) {
    // Get the current monitor
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    if (monitor == nullptr)
        return;

    // Get the monitor's video mode
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    if (mode == nullptr)
        return;

    // Set the window to fullscreen mode
    glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
}

void GraphicsContext::SetWindowMode(const EWindowMode mode) const {
    switch (mode) {
        case EWindowMode::Windowed:
            SetWindowedMode(mWindow.get(), CAST<int>(mWidthCurrent), CAST<int>(mHeightCurrent));
            break;
        case EWindowMode::Borderless:
            SetBorderlessFullscreenMode(mWindow.get());
            break;
        case EWindowMode::Fullscreen:
            SetFullscreenMode(mWindow.get());
            break;
    }
}

void GraphicsContext::SetWindowTitle(const str& title) const {
    glfwSetWindowTitle(GetWindow(), title.c_str());
}

void GraphicsContext::SetVSyncEnabled(bool enable) {
    glfwSwapInterval(enable);
}

void GraphicsContext::SetResolution(int width, int height) {
    glfwSetWindowSize(GetWindow(), width, height);
    glViewport(0, 0, width, height);
    OnResize(width, height);
}

void GraphicsContext::GetResolution(int& width, int& height) const {
    width  = CAST<int>(mWidthCurrent);
    height = CAST<int>(mHeightCurrent);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void GraphicsContext::BeginFrame() const {  // NOLINT(*-convert-member-functions-to-static)
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
    mDispatcher->Dispatch(ResolutionChangedEvent(CAST<i32>(width), CAST<i32>(height)));
}