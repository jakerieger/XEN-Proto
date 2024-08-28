// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Ball.h"
#include "Core/SceneContext.h"

#include <random>

static constexpr auto kBallSpeed = 10.f;

Ball::Ball(Player* player, Opponent* opponent, GameManager* manager)
    : mSprite(None), mTransform(None), mStartPosition({0.f, 0.f}), mPlayer(player),
      mOpponent(opponent), mGameManager(manager) {}

void Ball::Awake(const Shared<SceneContext>& context) {
    mTransform = AddComponent<Transform>();
    mSprite    = AddComponent<SpriteRenderer>("Assets/Sprites/ball.png", mTransform);
    mTransform->SetPosition(mStartPosition);

    // Set a random initial velocity
    Reset(false);

    mContext = context;

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
    CheckOutOfBounds();
}

void Ball::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    mSprite->Draw(camera->GetViewMatrix(),
                  camera->GetProjectionMatrix(),
                  mTransform->GetModelMatrix());
}

static glm::vec2 Reflection(const glm::vec2& velocity, const glm::vec2& normal) {
    const auto VdotN = glm::dot(velocity, normal);
    return velocity - (2 * VdotN) * normal;
}

void Ball::CheckCollision() {
    static constexpr auto kPlayerNormal   = glm::vec2(1, 0);
    static constexpr auto kOpponentNormal = glm::vec2(-1, 0);
    static constexpr auto kTopNormal      = glm::vec2(0, 1);
    static constexpr auto kBottomNormal   = glm::vec2(0, -1);

    const auto newPosition = mTransform->GetPosition() + mVelocity;

    const auto ballBounds     = mTransform->GetBounds();
    const auto playerBounds   = mPlayer->GetComponent<Transform>()->GetBounds();
    const auto opponentBounds = mOpponent->GetComponent<Transform>()->GetBounds();

    const auto topBounds = Rect(mViewport.Left, mViewport.Top + 1, mViewport.Right, mViewport.Top);
    const auto bottomBounds =
      Rect(mViewport.Left, mViewport.Bottom, mViewport.Right, mViewport.Bottom - 1);

    if (Transform::IsColliding(ballBounds, topBounds)) {
        mTransform->SetPosition(mTransform->GetPosition() - (mVelocity * 1.f));
        mVelocity = Reflection(mVelocity, kTopNormal);
        PlaySound(mContext.lock(), "impact", "Assets/Audio/impact.wav", 0.2f);
        return;
    }

    if (Transform::IsColliding(ballBounds, bottomBounds)) {
        mTransform->SetPosition(mTransform->GetPosition() + (mVelocity * 1.f));
        mVelocity = Reflection(mVelocity, kBottomNormal);
        PlaySound(mContext.lock(), "impact", "Assets/Audio/impact.wav", 0.2f);
        return;
    }

    if (Transform::IsColliding(ballBounds, playerBounds)) {
        mTransform->SetPosition(mTransform->GetPosition() - (mVelocity * 1.f));
        mVelocity = Reflection(mVelocity, kPlayerNormal);
        PlaySound(mContext.lock(), "impact", "Assets/Audio/impact.wav", 0.2f);
        return;
    }

    if (Transform::IsColliding(ballBounds, opponentBounds)) {
        mTransform->SetPosition(mTransform->GetPosition() - (mVelocity * 1.f));
        mVelocity = Reflection(mVelocity, kOpponentNormal);
        PlaySound(mContext.lock(), "impact", "Assets/Audio/impact.wav", 0.2f);
        return;
    }

    mTransform->SetPosition(newPosition);
}

void Ball::CheckOutOfBounds() {
    const auto position = mTransform->GetPosition();
    if (CAST<int>(position.x) < mViewport.Left) {
        // Player scored
        mGameManager->PlayerScored();
        Reset(true);
    }

    if (CAST<int>(position.x) > mViewport.Right) {
        // Opponent scored
        mGameManager->OpponentScored();
        Reset(false);
    }
}

static f32 GetRandomNumber(f32 min, f32 max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<f32> dis(min, max);
    return dis(gen);
}

void Ball::Reset(bool playerScored) {
    mTransform->SetPosition({0.f, 0.f});
    mVelocity = {playerScored ? -kBallSpeed : kBallSpeed, GetRandomNumber(0.f, 4.f)};
}