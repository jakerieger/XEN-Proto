// Author: Jake Rieger
// Created: 9/1/2024.
//

#include "Player.h"

#include "Bullet.h"
#include "XnCore/SceneContext.h"
#include "XnCore/InputEvents.h"
#include "XnCore/InputMap.h"

void Player::Awake(const Shared<SceneContext>& context) {
    mTransform = AddComponent<Transform>();
    mSprite    = AddComponent<SpriteRenderer>("Assets/Sprites/ship.png", mTransform);
    mTransform->SetPosition({0.f, 0.f});

    mContext = context;

    IGameObject::Awake(context);
}

void Player::Update(const Shared<SceneContext>& context, f32 dT) {
    IGameObject::Update(context, dT);
}

void Player::Destroyed(const Shared<SceneContext>& context) {
    IGameObject::Destroyed(context);
}

void Player::Draw(const Shared<SceneContext>& context) {
    const auto camera = context->MainCamera;
    mSprite->Draw(camera->GetViewMatrix(),
                  camera->GetProjectionMatrix(),
                  mTransform->GetModelMatrix());
}

void Player::OnMouseMove(const FMouseMoveEvent& event, const FInputMap& input) {}

void Player::OnKeyDown(const FKeyEvent& event, const FInputMap& input) {
    const auto shoot = input.GetInputMapping("Shoot");

    static int bullets = 0;
    if (event.KeyCode == GetKeyCode(shoot)) {
        const auto fmt = std::format("Bullet_{}", ++bullets);

        // Get player rotation in radians
        constexpr auto rotation     = 1.f;
        constexpr auto baseVelocity = 4.f;
        auto velocity               = rotation * baseVelocity;

        Instantiate<Bullet>(fmt, mContext.lock(), glm::vec2 {0.f, 0.f}, glm::vec2 {0.f, velocity});
    }
}