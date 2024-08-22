// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Core/GameObject.h"

using namespace GameObject::Traits;

class Player final : public IGameObject,
                     public IDrawable,
                     public IInputListener,
                     public IPhysicsObject {
public:
    Player();

    // IGameObject
    void Awake(const Shared<SceneContext>& context) override;
    void Update(const Shared<SceneContext>& context, f32 dT) override;
    void LateUpdate(const Shared<SceneContext>& context) override;
    void Destroyed(const Shared<SceneContext>& context) override;

    // IPhysicsUpdate
    void PhysicsUpdate(const Shared<SceneContext>& context) override;

    // IDrawable
    void Draw(const Shared<SceneContext>& context) override;
};
