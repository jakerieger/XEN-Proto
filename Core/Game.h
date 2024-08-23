// Author: Jake Rieger
// Created: 8/20/2024.
//

#pragma once

#include "Clock.h"
#include "Config.h"
#include "GraphicsContext.h"
#include "InputManager.h"
#include "Scene.h"
#include "Shared/Types.h"

class IGame {
public:
    explicit IGame(const str& title);
    virtual ~IGame() = default;
    void Run();

    [[nodiscard]] bool IsRunning() const;
    [[nodiscard]] bool IsPaused() const;
    [[nodiscard]] Shared<Scene> GetActiveScene() const;
    [[nodiscard]] GraphicsContext* GetGraphicsContext() const;
    [[nodiscard]] Shared<Config> GetEngineConfig() const;

    void AddScene(const str& name, const Shared<Scene>& scene);
    void RemoveScene(const str& name);
    void RemoveAllScenes();
    void LoadScene(const str& name);
    void UnloadScene(const str& name);

    void Pause();
    void Resume();

    void SetWindowIcon(const Path& icon) const;

protected:
    virtual void Initialize() = 0;
    virtual void Shutdown();

    str mTitle;
    bool mPaused = false;

    Shared<Scene> mActiveScene;
    Shared<Config> mConfig;

    Unique<GraphicsContext> mGraphicsContext;
    Unique<Clock> mClock;
    Unique<InputManager> mInputManager;

    Dictionary<str, Shared<Scene>> mScenes;

private:
    void CreateResources();
    void RenderThread() const;
};
