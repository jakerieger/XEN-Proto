// Author: Jake Rieger
// Created: 8/20/2024.
//

#include "Game.h"

#include <iostream>

IGame::IGame(const str& title) {
    mConfig = std::make_shared<EngineConfig>();
    try {
        mConfig->LoadConfig("EngineConfig.ini");
    } catch (RuntimeError& ex) {
        std::cerr << "[IGame::IGame] " << ex.what() << ", using defaults." << std::endl;
    }
    mTitle = title;
}

static void PhysicsThread(const IGame* game) {
    while (game->IsRunning()) {
        if (!game->IsPaused()) {
            for (const auto& go : game->GetActiveScene()->GetGameObjects()) {
                go->PhysicsUpdate();
            }
        }

        const auto timestep = 1.f / game->GetEngineConfig()->GetInternalConfig().PhysicsTimestep;
        std::this_thread::sleep_for(std::chrono::duration<f32>(timestep));
    }
}

void IGame::Run() {
    CreateResources();

    // Call user-defined init code
    Initialize();

    auto physicsThread = Thread(PhysicsThread, this);

    if (mActiveScene) {
        mActiveScene->Awake();
    }

    // Game loop
    static f32 dT        = 0.f;
    static auto lastTime = std::chrono::high_resolution_clock::now();
    while (IsRunning()) {
        auto currentTime                     = std::chrono::high_resolution_clock::now();
        std::chrono::duration<f32> deltaTime = currentTime - lastTime;
        lastTime                             = currentTime;
        dT                                   = deltaTime.count();

        if (!mPaused) {
            if (mActiveScene) {
                mActiveScene->Update(dT);
            }

            RenderThread();

            if (mActiveScene) {
                mActiveScene->LateUpdate();
            }
        }

        // Calculate timestep
        const auto timestep = 1.f / mConfig->GetInternalConfig().FixedTimestep;
        std::this_thread::sleep_for(std::chrono::duration<f32>(timestep));
    }

    if (mActiveScene) {
        mActiveScene->Destroyed();
    }

    physicsThread.join();

    // Call shutdown code
    Shutdown();
}

void IGame::Shutdown() {
    mGraphicsContext.reset();
    mThreadPool.reset();
    mActiveScene.reset();
}

void IGame::CreateResources() {
    mGraphicsContext = std::make_unique<GraphicsContext>(mConfig, mTitle);

    // TODO: Query user's computer to determine max number of threads
    mThreadPool = std::make_unique<ThreadPool>(4);

    mActiveScene = std::make_shared<Scene>();
}

bool IGame::IsRunning() const {
    return !glfwWindowShouldClose(mGraphicsContext->GetWindow());
}

bool IGame::IsPaused() const {
    return mPaused;
}

Shared<Scene> IGame::GetActiveScene() const {
    return mActiveScene;
}

GraphicsContext* IGame::GetGraphicsContext() const {
    return mGraphicsContext.get();
}

ThreadPool* IGame::GetThreadPool() const {
    return mThreadPool.get();
}

Shared<EngineConfig> IGame::GetEngineConfig() const {
    return mConfig;
}

void IGame::RenderThread() const {
    mGraphicsContext->BeginFrame();

    // Do rendering here
    {
        if (mActiveScene) {
            mActiveScene->Render();
        }
    }

    mGraphicsContext->EndFrame();
}