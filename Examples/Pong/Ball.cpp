// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Ball.h"
#include "Core/SceneContext.h"

Ball::Ball(Player* player, Opponent* opponent, GameManager* manager)
    : mSprite(None), mTransform(None), mStartPosition({0.f, 0.f}), mPlayer(player),
      mOpponent(opponent), mGameManager(manager) {}

void Ball::Awake(const Shared<SceneContext>& context) {
    mTransform = AddComponent<Transform>();
    mSprite    = AddComponent<SpriteRenderer>("Assets/Sprites/ball.png", mTransform);
    mTransform->SetPosition(mStartPosition);

    mVelocity = {-10.f, 0.f};

    IGameObject::Awake(context);
}

void Ball::Update(const Shared<SceneContext>& context, f32 dT) {
    IGameObject::Update(context, dT);
}

void Ball::LateUpdate(const Shared<SceneContext>& context) {
    IGameObject::LateUpdate(context);
}

void Ball::Destroyed(const Shared<SceneContext>& context) {
    IGameObject::Destroyed(context);
}

void Ball::PhysicsUpdate(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera->As<OrthoCamera>();
    if (!camera)
        return;
    const auto viewport = camera->GetViewport();
    // Store camera viewport for checking if player is out-of-bounds
    mViewport = viewport;

    CheckCollision();
}

void Ball::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    mSprite->Draw(camera->GetViewMatrix(),
                  camera->GetProjectionMatrix(),
                  mTransform->GetModelMatrix());
}

void Ball::CheckCollision() {
    const auto newPosition = mTransform->GetPosition() + mVelocity;

    const auto ballBounds     = mTransform->GetBounds();
    const auto playerBounds   = mPlayer->GetComponent<Transform>()->GetBounds();
    const auto opponentBounds = mOpponent->GetComponent<Transform>()->GetBounds();

    if (Transform::IsColliding(ballBounds, playerBounds)) {
        mTransform->SetPosition(mTransform->GetPosition() - (mVelocity * 4.f));
        mVelocity = -mVelocity;
        return;
    }

    if (Transform::IsColliding(ballBounds, opponentBounds)) {
        mTransform->SetPosition(mTransform->GetPosition() - (mVelocity * 4.f));
        mVelocity = -mVelocity;
        return;
    }

    mTransform->SetPosition(newPosition);
}