// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "GameManager.h"
#include "Shared/Types.h"
#include "Core/GameObject.h"
#include "Core/Components/SpriteRenderer.h"
#include "Core/Components/Transform.h"

#include "Opponent.h"
#include "Player.h"

using namespace GameObject;

class Ball final : public IGameObject,
                   public Traits::IDrawable,
                   public Traits::IPhysicsObject {
public:
    Ball(Player* player, Opponent* opponent, GameManager* manager);

    // IGameObject
    void Awake(const Shared<SceneContext>& context) override;
    void Update(const Shared<SceneContext>& context, f32 dT) override;
    void LateUpdate(const Shared<SceneContext>& context) override;
    void Destroyed(const Shared<SceneContext>& context) override;

    // IPhysicsUpdate
    void PhysicsUpdate(const Shared<SceneContext>& context) override;

    // IDrawable
    void Draw(const Shared<SceneContext>& context) override;

private:
    SpriteRenderer* mSprite;
    Transform* mTransform;
    glm::vec2 mStartPosition;
    Rect mViewport;
    Player* mPlayer;
    Opponent* mOpponent;
    GameManager* mGameManager;
    glm::vec2 mVelocity = {0.f, 0.f};

    void CheckCollision();
};
