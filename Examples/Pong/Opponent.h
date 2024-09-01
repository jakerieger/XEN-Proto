// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "XnCore/GameObject.h"
#include "XnCore/Components/SpriteRenderer.h"
#include "XnCore/Components/Transform.h"

using namespace GameObject;

class Opponent final : public IGameObject,
                       public Traits::IDrawable,
                       public Traits::IPhysicsObject {
public:
    Opponent();

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
    glm::vec2 mVelocity = {0.f, 10.f};

    [[nodiscard]] bool OutOfBounds(const glm::vec2& position) const;
};
