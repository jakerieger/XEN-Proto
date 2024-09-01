// Author: Jake Rieger
// Created: 8/20/2024.
//

#include "Game.h"
#include "Events.h"
#include "XnProfiler/Profiler.h"

#include <iostream>

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
    Create();

    // Pass physics updating to its own thread running at its own fixed timestep
    auto physicsThread = Thread(PhysicsThread, this);

    // Game loop
    mClock->Start();
    Profiler::Begin(mTitle);
    while (IsRunning()) {
        mClock->Tick();

        if (!mPaused) {
            Profiler::TimePoint start = Profiler::BeginContext();
            if (mActiveScene) {
                mActiveScene->Update(mClock->GetDeltaTime());
            }
            Profiler::EndContext(start, "SceneUpdate");

            start = Profiler::BeginContext();
            RenderThread();
            Profiler::EndContext(start, "Render");

            start = Profiler::BeginContext();
            if (mActiveScene) {
                mActiveScene->LateUpdate();
            }
            Profiler::EndContext(start, "LateUpdate");
        }

        mClock->Update();
    }
    Profiler::End();
    mClock->Stop();

    RemoveAllScenes();
    physicsThread.join();
    mInputManager->SetShouldDispatch(false);
    Destroy();
}

void IGame::Destroy() {
    mGraphicsContext.reset();
    mClock.reset();
    mInputManager.reset();
}

void IGame::CreateResources() {
    mEventDispatcher = std::make_unique<EventDispatcher>();
    mEventDispatcher->RegisterListener<ResolutionChangedEvent>(
      [this](const ResolutionChangedEvent& event) {
          OnResolutionChange(event.Width, event.Height);
      });

    mGraphicsContext = std::make_unique<GraphicsContext>(mConfig, mTitle, mEventDispatcher);
    mClock           = std::make_unique<Clock>();
    mInputManager =
      std::make_unique<InputManager>(mGraphicsContext->GetWindow(), mConfig->GetInputMap());
    mInputManager->SetShouldDispatch(true);

    mAudioContext = std::make_shared<AudioContext>(mConfig, mEventDispatcher);
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

InputManager* IGame::GetInputManager() const {
    return mInputManager.get();
}

AudioContext* IGame::GetAudioContext() const {
    return mAudioContext.get();
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

Shared<Scene> IGame::CreateScene(const str& name) {
    mScenes[name] = std::make_shared<Scene>(mEventDispatcher);
    return mScenes[name];
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

void IGame::OnResolutionChange(int width, int height) {
    // TODO: Notify necessary resources that the viewport resolution has changed
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