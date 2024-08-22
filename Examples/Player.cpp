// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Player.h"
#include "Core/SceneContext.h"

#include <glm/ext/matrix_transform.hpp>

Player::Player() = default;

void Player::Awake(const Shared<SceneContext>& context) {
    mSprite = std::make_unique<Sprite>("Assets/Sprites/paddle_player.png");
}

void Player::Update(const Shared<SceneContext>& context, f32 dT) {}

void Player::LateUpdate(const Shared<SceneContext>& context) {}

void Player::Destroyed(const Shared<SceneContext>& context) {
    mSprite.reset();
}

void Player::PhysicsUpdate(const Shared<SceneContext>& context) {
    // TODO: Update paddle movement and collision here
}

void Player::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    mSprite->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix(), mSprite->GetModel());
}