// Author: Jake Rieger
// Created: 8/20/2024.
//

#pragma once

#include "Clock.h"
#include "Config.h"
#include "EventSystem.h"
#include "GraphicsContext.h"
#include "InputManager.h"
#include "Scene.h"
#include "Shared/Types.h"

/// @brief This is the core interface of a game application.
///
/// The Game class is responsible for managing all game resources,
/// such as scenes, input, rendering, and windows.
///
/// The only thing required in the `main()` function of your application
/// is an instance of your IGame implementation and to call `Run()` on said instance:
/// @code
/// int main() {
///     MyGame game;
///     game.Run();
///     return 0;
/// }
/// @endcode
class IGame {
public:
    explicit IGame(const str& title);
    virtual ~IGame() = default;

    /// @brief Creates game resources and starts the game loop, cleaning up and shutting down
    /// once the game exits.
    void Run();

    /// @brief Returns the running status of the game application.
    [[nodiscard]] bool IsRunning() const;

    /// @brief Returns the paused status of the game. This can be used to pause updating
    /// but allow the game to continue running in the background.
    [[nodiscard]] bool IsPaused() const;

    /// @brief Returns the active game scene.
    [[nodiscard]] Shared<Scene> GetActiveScene() const;

    /// @brief Returns the graphics context, which owns the game application's window.
    [[nodiscard]] GraphicsContext* GetGraphicsContext() const;

    /// @brief Returns the game's configuration, typically loaded from a `Config.ini` file
    /// in the game's root directory.
    [[nodiscard]] Shared<Config> GetEngineConfig() const;

    void AddScene(const str& name, const Shared<Scene>& scene);
    void RemoveScene(const str& name);
    void RemoveAllScenes();
    void LoadScene(const str& name);
    void UnloadScene(const str& name);

    void Pause();
    void Resume();

    /// @brief Set's the game window's icon from a png file.
    ///
    /// @note This will not change the executable's icon. In order to change that,
    /// modify the necessary platform-specific resource files (ex, .rc files on windows).
    void SetWindowIcon(const Path& icon) const;

    void OnResolutionChange(int width, int height);

    virtual void Create() = 0;
    virtual void Destroy();

protected:
    str mTitle;
    bool mPaused = false;

    Shared<Scene> mActiveScene;
    Shared<Config> mConfig;
    Shared<EventDispatcher> mEventDispatcher;

    Unique<GraphicsContext> mGraphicsContext;
    Unique<Clock> mClock;
    Unique<InputManager> mInputManager;

    Dictionary<str, Shared<Scene>> mScenes;

private:
    void CreateResources();
    void RenderThread() const;
};
