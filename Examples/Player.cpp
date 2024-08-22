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

static glm::mat4 ViewMatrix() {
    auto view = glm::mat4(1.f);

    // f32 targetX = 0.f;
    // f32 targetY = 0.f;
    // if (g_FollowTarget) {
    //     const auto targetPos = g_FollowTarget->GetTransform()->GetPosition();
    //     if (g_PreviousTargetPosition == glm::vec2(0.f)) {
    //         g_PreviousTargetPosition = targetPos;
    //     }
    //
    //     const auto lerpedX =
    //       g_PreviousTargetPosition.x + k_LerpFactor * (targetPos.x - g_PreviousTargetPosition.x);
    //     g_PreviousTargetPosition.x = lerpedX;
    //     targetX                    = lerpedX;
    //
    //     const auto lerpedY = g_PreviousTargetPosition.y +
    //                          (k_LerpFactor / 3.f) * (targetPos.y - g_PreviousTargetPosition.y);
    //     g_PreviousTargetPosition.y = lerpedY;
    //     targetY                    = lerpedY + k_OffsetY;
    // }
    // // TODO: Handle Y following differently from simply lerping to target Y
    // view = glm::translate(view, {-targetX, -targetY + 10.f, 0.f});

    return view;
}

static glm::mat4 ProjectionMatrix() {
    const f32 w       = 1280;
    const f32 h       = 720;
    const float ratio = w / h;
    glm::vec2 extents(ratio * 25.0f, 25.0f);
    extents *= 1.f;

    const glm::vec2 lower = glm::vec2(0.f, 25.f) - extents;
    const glm::vec2 upper = glm::vec2(0.f, 25.f) + extents;

    // X Axis vector
    const glm::vec4 x = {2.0f / (upper.x - lower.x), 0.f, 0.f, 0.f};
    // Y Axis vector
    const glm::vec4 y = {0.f, 2.0f / (upper.y - lower.y), 0.f, 0.f};
    // Z Axis Vector
    constexpr glm::vec4 z = {0.f, 0.f, 1.0f, 0.f};
    // Zoom(??) vector
    const glm::vec4 zm = {-(upper.x + lower.x) / (upper.x - lower.x),
                          -(upper.y + lower.y) / (upper.y - lower.y),
                          0.f,
                          1.f};

    glm::mat4 m(1.f);
    m[0] = x;
    m[1] = y;
    m[2] = z;
    m[3] = zm;

    return m;
}

void Player::Draw(const Shared<SceneContext>& context) {
    mSprite->Draw(ViewMatrix(), ProjectionMatrix(), mSprite->GetModel());
}