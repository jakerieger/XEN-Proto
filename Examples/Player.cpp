// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Player.h"

#include "Core/PipelineStates.h"
#include "Core/SceneContext.h"

Player::Player() : mTransform(None) {}

void Player::Awake(const Shared<SceneContext>& context) {
    mTransform = AddComponent<Transform>();
    mSprite    = std::make_unique<Sprite>("Assets/Sprites/paddle_player.png");

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
    mSprite.reset();
}

void Player::PhysicsUpdate(const Shared<SceneContext>& context) {
    // TODO: Update paddle movement and collision here
}

void Player::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    PipelineStates::DrawWire();
    mSprite->Draw(camera->GetViewMatrix(), camera->GetProjectionMatrix(), mSprite->GetModel());
}