// Author: Jake Rieger
// Created: 8/20/2024.
//

#pragma once

#include "AudioContext.h"
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
    explicit IGame(const str& title, const Path& dataPath);
    virtual ~IGame() = default;

    void Initialize(GLFWwindow* window);
    void Shutdown();
    void RequestFrame() const;

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

    [[nodiscard]] InputManager* GetInputManager() const;

    [[nodiscard]] AudioContext* GetAudioContext() const;

    void AddScene(const str& name, const Shared<Scene>& scene);
    void RemoveScene(const str& name);
    void RemoveAllScenes();
    void LoadScene(const str& name);
    void UnloadScene(const str& name);

    Shared<Scene> CreateScene(const str& name);

    void Pause();
    void Resume();
    void Quit() const;

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
    Path mDataPath;

    Shared<Scene> mActiveScene;
    Shared<Config> mConfig;
    Shared<EventDispatcher> mEventDispatcher;
    Shared<AudioContext> mAudioContext;

    Unique<GraphicsContext> mGraphicsContext;
    Unique<Clock> mClock;
    Unique<InputManager> mInputManager;

    Dictionary<str, Shared<Scene>> mScenes;

    Thread mPhysicsThread;

    /// @brief Creates a new instance of T and adds it to the supplied scene.
    /// @return Shared pointer to T instance.
    template<typename T, typename... Args>
    Shared<T> CreateGameObject(const Shared<Scene>& scene, Args&&... args) {
        auto go = std::make_shared<T>(std::forward<Args>(args)...);
        scene->AddGameObject(go);
        return go;
    }

private:
    void CreateResources(GLFWwindow* window);
    void RenderThread() const;
};
