// Author: Jake Rieger
// Created: 8/20/2024.
//

#include "Game.h"

#include <iostream>
#include <ranges>

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
            if (game->GetActiveScene()) {
                game->GetActiveScene()->PhysicsUpdate();
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

    // Pass physics updating to its own thread running at its own fixed timestep
    auto physicsThread = Thread(PhysicsThread, this);

    // Game loop
    mClock->Start();
    while (IsRunning()) {
        mClock->Tick();

        if (!mPaused) {
            if (mActiveScene) {
                mActiveScene->Update(mClock->GetDeltaTime());
            }

            RenderThread();

            if (mActiveScene) {
                mActiveScene->LateUpdate();
            }
        }

        mClock->Update();
    }
    mClock->Stop();

    RemoveAllScenes();
    physicsThread.join();
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

    mClock = std::make_unique<Clock>();
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

void IGame::AddScene(const str& name, const Shared<Scene>& scene) {
    mScenes[name] = scene;
}

void IGame::RemoveScene(const str& name) {
    const auto scene = mScenes.find(name);
    if (scene != mScenes.end()) {
        scene->second->Destroyed();
        mScenes.erase(name);
    }
}

void IGame::RemoveAllScenes() {
    for (const auto& [name, scene] : mScenes) {
        scene->Destroyed();
        std::cout << "(Info) Unloaded scene: \"" << name << "\"\n";
    }

    mScenes.clear();
}

void IGame::LoadScene(const str& name) {
    const auto scene = mScenes.find(name);
    if (scene != mScenes.end()) {
        mActiveScene = scene->second;
        mActiveScene->Awake();
        std::cout << "(Info) Loaded scene: \"" << name << "\"\n";
    }
}

void IGame::UnloadScene(const str& name) {
    const auto scene = mScenes.find(name);
    if (scene != mScenes.end()) {
        scene->second->Destroyed();
        std::cout << "(Info) Unloaded scene: \"" << name << "\"\n";
    }
}

void IGame::Pause() {
    mPaused = true;
}

void IGame::Resume() {
    mPaused = false;
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