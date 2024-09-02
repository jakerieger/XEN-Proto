// Author: Jake Rieger
// Created: 8/30/2024.
//

#include "InterfaceContext.h"

InterfaceContext::InterfaceContext(GLFWwindow* window, int width, int height) {
    /*Rml::String renderMsg;
    if (!RmlGL3::Initialize(&renderMsg)) {
        throw RuntimeError(renderMsg);
    }

    mSystemInterface = std::make_unique<SystemInterface_GLFW>();
    mRenderInterface = std::make_unique<RenderInterface_GL3>();

    mSystemInterface->SetWindow(window);
    mRenderInterface->SetViewport(width, height);

    Rml::SetSystemInterface(mSystemInterface.get());
    Rml::SetRenderInterface(mRenderInterface.get());
    if (!Rml::Initialise()) {
        throw RuntimeError("Failed to initialize RmlUi");
    }

    mRmlContext = Unique<Rml::Context>(Rml::CreateContext("main", {width, height}));
    if (!mRmlContext) {
        throw RuntimeError("Failed to create Rml context");
    }

    if (!Rml::Debugger::Initialise(mRmlContext.get())) {
        Rml::Shutdown();
        throw RuntimeError("Failed to initialize Rml debugger");
    }

    const auto result = IO::ReadAllBytes("BuiltinAssets/Fonts/ChakraPetch-Regular.ttf");
    if (!result.has_value()) {
        throw RuntimeError("Failed to read font file");
    }
    const auto& fontBytes = result.value();
    if (!Rml::LoadFontFace(fontBytes.data(),
                           CAST<int>(fontBytes.size()),
                           "ChakraPetch",
                           Rml::Style::FontStyle::Normal)) {
        Rml::Shutdown();
        throw RuntimeError("Failed to load font file");
    }*/
}

InterfaceContext::~InterfaceContext() {
    /*Rml::Shutdown();
    RmlGL3::Shutdown();

    mSystemInterface.reset();
    mRenderInterface.reset();
    mRmlContext.reset();*/
}