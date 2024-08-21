// Author: Jake Rieger
// Created: 8/20/2024.
//

#include "Game.h"

IGame::IGame(const str& title) {
    mConfig = std::make_shared<EngineConfig>();
    mConfig->LoadConfig("EngineConfig.ini");

    mWidth  = mConfig->GetRenderingConfig().Width;
    mHeight = mConfig->GetRenderingConfig().Height;
    mTitle  = title;
}

void IGame::Run() {
    CreateResources();

    // Call user-defined init code
    Initialize();

    // Game loop
    while (IsRunning()) {
        mGraphicsContext->BeginFrame();

        // Do rendering here
        {}

        mGraphicsContext->EndFrame();
    }

    // Call shutdown code
    Shutdown();
}

void IGame::Shutdown() {
    mGraphicsContext.reset();
    mThreadPool.reset();
}
void IGame::CreateResources() {
    mGraphicsContext = std::make_unique<GraphicsContext>(mConfig, mTitle);

    // TODO: Query user's computer to determine max number of threads
    // mThreadPool = std::make_unique<ThreadPool>(ThreadPool::GetMaxThreadCount());
}
bool IGame::IsRunning() const {
    return !glfwWindowShouldClose(mGraphicsContext->GetWindow());
}