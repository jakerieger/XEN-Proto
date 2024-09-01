// Author: Jake Rieger
// Created: 8/30/2024.
//

#pragma once

#include "Shared/Types.h"

#include <RmlUi/Core.h>
#include <RmlUi/Debugger.h>
#include <RmlUi/RmlUi_Platform_GLFW.h>
#include <RmlUi/RmlUi_Renderer_GL3.h>

class InterfaceContext {
public:
    InterfaceContext(GLFWwindow* window, int width, int height);
    ~InterfaceContext();

private:
    Unique<SystemInterface_GLFW> mSystemInterface = None;
    Unique<RenderInterface_GL3> mRenderInterface  = None;
    Unique<Rml::Context> mRmlContext              = None;
};
