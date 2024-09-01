// Author: Jake Rieger
// Created: 9/1/2024.
//

#include "Bullet.h"

#include "XnCore/SceneContext.h"

Bullet::Bullet(const str& name, const glm::vec2& position, const glm::vec2& velocity)
    : IGameObject(name) {
    mInitialPosition = position;
    mVelocity        = velocity;

    // TODO: THIS DOES NOT DESPAWN
}

void Bullet::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    mSprite->Draw(camera->GetViewMatrix(),
                  camera->GetProjectionMatrix(),
                  mTransform->GetModelMatrix());
}

void Bullet::Awake(const Shared<SceneContext>& context) {
    mTransform = AddComponent<Transform>();
    mSprite    = AddComponent<SpriteRenderer>("Assets/Sprites/bullet.png", mTransform);
    mTransform->SetPosition(mInitialPosition);

    IGameObject::Awake(context);
}

void Bullet::Update(const Shared<SceneContext>& context, f32 dT) {
    IGameObject::Update(context, dT);
}

void Bullet::PhysicsUpdate(const Shared<SceneContext>& context) {
    // TODO: This causes crashes occasionally, probably a dangling pointer somewhere
    if (mFrame >= mLifetime) {
        Destroy(context);
        return;
    }

    const auto position    = mTransform->GetPosition();
    const auto newPosition = (position + mVelocity);
    mTransform->SetPosition(newPosition);

    mFrame++;
}

void Bullet::Destroyed(const Shared<SceneContext>& context) {
    IGameObject::Destroyed(context);
}