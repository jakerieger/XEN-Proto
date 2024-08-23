// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Opponent.h"
#include "Core/SceneContext.h"

Opponent::Opponent() : mSprite(None), mTransform(None) {}

void Opponent::Awake(const Shared<SceneContext>& context) {
    mTransform = AddComponent<Transform>();
    mSprite    = AddComponent<SpriteRenderer>("Assets/Sprites/paddle_opponent.png", mTransform);
    mTransform->SetPosition({-540, 0});

    IGameObject::Awake(context);
}

void Opponent::Update(const Shared<SceneContext>& context, f32 dT) {
    IGameObject::Update(context, dT);
}

void Opponent::LateUpdate(const Shared<SceneContext>& context) {
    IGameObject::LateUpdate(context);
}

void Opponent::Destroyed(const Shared<SceneContext>& context) {
    IGameObject::Destroyed(context);
}

void Opponent::PhysicsUpdate(const Shared<SceneContext>& context) {
    // TODO: Update paddle movement and collision here
}

void Opponent::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    mSprite->Draw(camera->GetViewMatrix(),
                  camera->GetProjectionMatrix(),
                  mTransform->GetModelMatrix());
}