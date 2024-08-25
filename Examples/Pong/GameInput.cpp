// Author: Jake Rieger
// Created: 8/25/2024.
//

#include "GameInput.h"
#include "Core/InputMap.h"

GameInput::GameInput(GraphicsContext* context) {
    mGraphicsContext = context;
}

void GameInput::Awake(const Shared<SceneContext>& context) {
    IGameObject::Awake(context);
}
void GameInput::Update(const Shared<SceneContext>& context, f32 dT) {
    IGameObject::Update(context, dT);
}
void GameInput::LateUpdate(const Shared<SceneContext>& context) {
    IGameObject::LateUpdate(context);
}
void GameInput::Destroyed(const Shared<SceneContext>& context) {
    IGameObject::Destroyed(context);
}
void GameInput::OnKeyDown(const FKeyEvent& event, const FInputMap& input) {
    IInputListener::OnKeyDown(event, input);

    const auto resolution1      = input.GetInputMapping("Resolution1");
    const auto resolution2      = input.GetInputMapping("Resolution2");
    const auto resolution3      = input.GetInputMapping("Resolution3");
    const auto resolution4      = input.GetInputMapping("Resolution4");
    const auto toggleVsync      = input.GetInputMapping("ToggleVsync");
    const auto toggleFullscreen = input.GetInputMapping("ToggleFullscreen");

    if (event.KeyCode == GetKeyCode(resolution1)) {
        mGraphicsContext->SetResolution(800, 600);
    }
}