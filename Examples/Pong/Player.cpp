// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Player.h"
#include "Core/InputMap.h"
#include "Core/SceneContext.h"

Player::Player() : mSprite(None), mTransform(None), mStartPosition({540, 0}) {}

void Player::Awake(const Shared<SceneContext>& context) {
    mTransform = AddComponent<Transform>();
    mSprite    = AddComponent<SpriteRenderer>("Assets/Sprites/paddle_player.png", mTransform);
    mTransform->SetPosition(mStartPosition);

    IGameObject::Awake(context);
}

void Player::Update(const Shared<SceneContext>& context, f32 dT) {
    IGameObject::Update(context, dT);
}

void Player::LateUpdate(const Shared<SceneContext>& context) {
    IGameObject::LateUpdate(context);
}

void Player::Destroyed(const Shared<SceneContext>& context) {
    IGameObject::Destroyed(context);
}

void Player::PhysicsUpdate(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera->As<OrthoCamera>();
    if (!camera)
        return;
    const auto viewport = camera->GetViewport();
    // Store camera viewport for checking if player is out-of-bounds
    mViewport = viewport;
}

void Player::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    mSprite->Draw(camera->GetViewMatrix(),
                  camera->GetProjectionMatrix(),
                  mTransform->GetModelMatrix());
}

void Player::OnKey(const FKeyEvent& event, const FInputMap& input) {
    IInputListener::OnKey(event, input);

    const auto moveUp   = input.GetInputMapping("MoveUp");
    const auto moveDown = input.GetInputMapping("MoveDown");

    if (event.KeyCode == GetKeyCode(moveUp)) {
        const glm::vec2 newPosition = {mTransform->GetPosition().x,
                                       mTransform->GetPosition().y + 10.f};
        if (!OutOfBounds(newPosition))
            mTransform->SetPosition(newPosition);
    }

    if (event.KeyCode == GetKeyCode(moveDown)) {
        const glm::vec2 newPosition = {mTransform->GetPosition().x,
                                       mTransform->GetPosition().y - 10.f};
        if (!OutOfBounds(newPosition))
            mTransform->SetPosition(newPosition);
    }
}

bool Player::OutOfBounds(const glm::vec2& position) const {
    // Check out of bounds
    const auto height = mTransform->GetScale().y;
    const auto top    = mViewport.Top;
    const auto bottom = mViewport.Bottom;

    const auto topBounds    = CAST<f32>(top) - height;
    const auto bottomBounds = CAST<f32>(bottom) + height;

    if (position.y > topBounds) {
        return true;
    }

    if (position.y < bottomBounds) {
        return true;
    }

    return false;
}