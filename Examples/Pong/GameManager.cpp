// Author: Jake Rieger
// Created: 8/25/2024.
//

#include "GameManager.h"
#include "Core/Events.h"
#include "Core/InputMap.h"
#include "Core/SceneContext.h"

GameManager::GameManager(GraphicsContext* context) {
    mGraphicsContext = context;
}

void GameManager::Awake(const Shared<SceneContext>& context) {
    IGameObject::Awake(context);

    const PlaySoundEvent backgroundMusic("music", "Assets/Audio/gameplay.wav", 0.1f, true);
    const auto dispatcher = context->EventSystem;
    dispatcher->Dispatch(backgroundMusic);
}
void GameManager::Update(const Shared<SceneContext>& context, f32 dT) {
    IGameObject::Update(context, dT);
}
void GameManager::LateUpdate(const Shared<SceneContext>& context) {
    IGameObject::LateUpdate(context);
}
void GameManager::Destroyed(const Shared<SceneContext>& context) {
    IGameObject::Destroyed(context);
}
void GameManager::OnKeyDown(const FKeyEvent& event, const FInputMap& input) {
    IInputListener::OnKeyDown(event, input);

    static bool fullscreen      = false;
    const auto toggleFullscreen = input.GetInputMapping("ToggleFullscreen");

    if (event.KeyCode == GetKeyCode(toggleFullscreen)) {
        mGraphicsContext->SetWindowMode(fullscreen ? EWindowMode::Windowed
                                                   : EWindowMode::Fullscreen);
        fullscreen = !fullscreen;
    }
}

void GameManager::PlayerScored() {
    mScorePlayer++;
}

void GameManager::OpponentScored() {
    mScoreOpponent++;
}