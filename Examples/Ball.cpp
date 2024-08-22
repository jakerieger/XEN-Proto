// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Ball.h"
#include "Core/SceneContext.h"

Ball::Ball() : mSprite(None), mTransform(None) {}

void Ball::Awake(const Shared<SceneContext>& context) {
    mTransform = AddComponent<Transform>();
    mSprite    = AddComponent<SpriteRenderer>("Assets/Sprites/ball.png", mTransform);

    IGameObject::Awake(context);
}

void Ball::Update(const Shared<SceneContext>& context, f32 dT) {
    IGameObject::Update(context, dT);

    mTransform->SetPosition({0, 0});
}

void Ball::LateUpdate(const Shared<SceneContext>& context) {
    IGameObject::LateUpdate(context);
}

void Ball::Destroyed(const Shared<SceneContext>& context) {
    IGameObject::Destroyed(context);
}

void Ball::PhysicsUpdate(const Shared<SceneContext>& context) {
    // TODO: Update paddle movement and collision here
}

void Ball::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    mSprite->Draw(camera->GetViewMatrix(),
                  camera->GetProjectionMatrix(),
                  mTransform->GetModelMatrix());
}