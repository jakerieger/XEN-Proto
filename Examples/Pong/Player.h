// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Core/GameObject.h"
#include "Core/Components/SpriteRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Config.h"

using namespace GameObject;

/**
 * Implement a game object for our player. Note that you can
 * extend a game object's capabilities by inheriting specific traits:
 * - Objects that are drawn on screen must inherit `IDrawable`.
 * - Objects that wish to receive input must inherit `IInputListener`.
 * - Objects that require fixed time-step updating must inherit `IPhysicsObject`.
 */
class Player final : public IGameObject,
                     public Traits::IDrawable,
                     public Traits::IInputListener,
                     public Traits::IPhysicsObject {
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

    // IInputListener
    void OnKey(const FKeyEvent& event, const FInputMap& input) override;
    void OnKeyDown(const FKeyEvent& event, const FInputMap& input) override;

private:
    SpriteRenderer* mSprite;
    Transform* mTransform;
    glm::vec2 mStartPosition;
    Rect mViewport;

    [[nodiscard]] bool OutOfBounds(const glm::vec2& position) const;
};
