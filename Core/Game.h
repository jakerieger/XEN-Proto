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
    IGame(const str& title);
    virtual ~IGame() = default;
    void Run();

protected:
    virtual void Initialize() = 0;
    virtual void Shutdown();

    u32 mWidth;
    u32 mHeight;
    str mTitle;

    Unique<ThreadPool> mThreadPool;
    Unique<GraphicsContext> mGraphicsContext;
    Vector<Shared<Scene>> mScenes;
    Shared<EngineConfig> mConfig;

private:
    void CreateResources();
    bool IsRunning() const;
};
