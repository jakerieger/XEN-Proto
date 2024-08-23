// Author: Jake Rieger
// Created: 8/20/2024.
//

#include "Game.h"

#include <iostream>
#include <ranges>

IGame::IGame(const str& title) {
    mConfig = std::make_shared<Config>();
    try {
        mConfig->LoadConfig("Config.ini");
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

        std::this_thread::sleep_for(std::chrono::milliseconds(4));
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

#ifndef NDEBUG
        // Show the frame rate in the window title for debugging purposes
        auto fmt = std::format("{} | FPS: {:.2f}", mTitle, mClock->GetFrameRate());
        glfwSetWindowTitle(mGraphicsContext->GetWindow(), fmt.c_str());
#endif
        mClock->Update();
    }
    mClock->Stop();

    RemoveAllScenes();
    physicsThread.join();
    mInputManager->SetShouldDispatch(false);
    Shutdown();
}

void IGame::Shutdown() {
    mGraphicsContext.reset();
    mClock.reset();
    mInputManager.reset();
}

void IGame::CreateResources() {
    mGraphicsContext = std::make_unique<GraphicsContext>(mConfig, mTitle);
    mClock           = std::make_unique<Clock>();
    mInputManager =
      std::make_unique<InputManager>(mGraphicsContext->GetWindow(), mConfig->GetInputMap());
    mInputManager->SetShouldDispatch(true);
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

Shared<Config> IGame::GetEngineConfig() const {
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
void IGame::SetWindowIcon(const Path& icon) const {
    mGraphicsContext->SetWindowIcon(icon);
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