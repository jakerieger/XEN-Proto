// Author: Jake Rieger
// Created: 8/20/2024.
//

#pragma once

#include "EngineConfig.h"
#include "GraphicsContext.h"
#include "Scene.h"
#include "ThreadPool.h"
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
    [[nodiscard]] ThreadPool* GetThreadPool() const;
    [[nodiscard]] Shared<EngineConfig> GetEngineConfig() const;

protected:
    virtual void Initialize() = 0;
    virtual void Shutdown();

    str mTitle;
    bool mPaused = false;

    Unique<ThreadPool> mThreadPool;
    Unique<GraphicsContext> mGraphicsContext;
    Shared<Scene> mActiveScene;
    Shared<EngineConfig> mConfig;

private:
    void CreateResources();
    void RenderThread() const;
};
