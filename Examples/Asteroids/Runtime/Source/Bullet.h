// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma once

#include "XnCore/GameObject.h"
#include "XnCore/Components/SpriteRenderer.h"

#include <glm/vec2.hpp>

class Bullet final : public IGameObject,
                     public GameObject::Traits::IDrawable,
                     public GameObject::Traits::IPhysicsObject {
public:
    Bullet(const str& name, const glm::vec2& position, const glm::vec2& velocity);
    void Draw(const Shared<SceneContext>& context) override;
    void Awake(const Shared<SceneContext>& context) override;
    void Update(const Shared<SceneContext>& context, f32 dT) override;
    void PhysicsUpdate(const Shared<SceneContext>& context) override;
    void Destroyed(const Shared<SceneContext>& context) override;

private:
    SpriteRenderer* mSprite = None;
    Transform* mTransform   = None;
    glm::vec2 mInitialPosition;
    glm::vec2 mVelocity;
    int mLifetime = 60;
    int mFrame    = 0;
};
