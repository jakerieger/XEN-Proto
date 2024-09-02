// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Opponent.h"
#include "XnCore/SceneContext.h"

Opponent::Opponent() : IGameObject("Opponent"), mSprite(None), mTransform(None), mStartPosition({-540, 0}) {}

void Opponent::Awake(const Shared<SceneContext>& context) {
    mTransform = AddComponent<Transform>();
    mSprite    = AddComponent<SpriteRenderer>("Assets/Sprites/paddle_opponent.png", mTransform);
    mTransform->SetPosition(mStartPosition);

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
    const auto camera = context->MainCamera->As<OrthoCamera>();
    if (!camera)
        return;
    const auto viewport = camera->GetViewport();
    // Store camera viewport for checking if player is out-of-bounds
    mViewport = viewport;

    // Move opponent paddle
    // const auto newPosition = mTransform->GetPosition() + mVelocity;
    // if (!OutOfBounds(newPosition)) {
    //     mTransform->SetPosition(newPosition);
    // } else {
    //     mVelocity.y = -mVelocity.y;
    // }
}

void Opponent::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    mSprite->Draw(camera->GetViewMatrix(),
                  camera->GetProjectionMatrix(),
                  mTransform->GetModelMatrix());
}

bool Opponent::OutOfBounds(const glm::vec2& position) const {
    // Check out of bounds
    const auto height = mTransform->GetScale().y;
    const auto top    = mViewport.Top;
    const auto bottom = mViewport.Bottom;

    const auto topBounds    = CAST<f32>(top) - height;
    const auto bottomBounds = CAST<f32>(bottom) + height;

    if (position.y > topBounds || position.y < bottomBounds) {
        return true;
    }

    return false;
}