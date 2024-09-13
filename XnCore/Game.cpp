// Author: Jake Rieger
// Created: 8/20/2024.
//

#include "Game.h"
#include "Events.h"

#include <iostream>

IGame::IGame(const str& title, const Path& dataPath) {
    mDataPath = dataPath;
    mConfig   = std::make_shared<Config>(dataPath);

    try {
        mConfig->LoadAudioConfig("Config/Audio.ini");
        mConfig->LoadInputMappings("Config/Input.ini");
        mConfig->LoadRenderingConfig("Config/Rendering.ini");
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

void IGame::Initialize(GLFWwindow* window) {
    CreateResources(window);

    // Call user-defined init code
    Create();

    mPhysicsThread = Thread(PhysicsThread, this);
    mClock->Start();
}

void IGame::Shutdown() {
    mClock->Stop();
    RemoveAllScenes();
    mPhysicsThread.join();
    mInputManager->SetShouldDispatch(false);
    Destroy();
}

void IGame::RequestFrame() const {
    mClock->Tick();

    if (mPaused) {
        RenderThread();
        return;
    }

    if (mActiveScene) {
        mActiveScene->Update(1.f);
    }

    RenderThread();

    if (mActiveScene) {
        mActiveScene->LateUpdate();
    }

    mClock->Update();
}

void IGame::Destroy() {
    mGraphicsContext.reset();
    mClock.reset();
    mInputManager.reset();
}

void IGame::CreateResources(GLFWwindow* window) {
    mEventDispatcher = std::make_unique<EventDispatcher>();
    mEventDispatcher->RegisterListener<ResolutionChangedEvent>(
      [this](const ResolutionChangedEvent& event) {
          OnResolutionChange(event.Width, event.Height);
      });

    mGraphicsContext = std::make_unique<GraphicsContext>(window, mConfig, mTitle, mEventDispatcher);
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
    mScenes[name] = std::make_shared<Scene>(mEventDispatcher, [](const Weak<SceneContext>&){});
    return mScenes[name];
}

void IGame::Pause() {
    mPaused = true;
}

void IGame::Resume() {
    mPaused = false;
}

void IGame::Quit() const {
    glfwSetWindowShouldClose(mGraphicsContext->GetWindow(), true);
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