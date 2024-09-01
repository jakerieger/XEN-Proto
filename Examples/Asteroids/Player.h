// Author: Jake Rieger
// Created: 9/1/2024.
//

#pragma once

#include "XnCore/GameObject.h"
#include "XnCore/Components/SpriteRenderer.h"

using namespace GameObject::Traits;

class Player final : public IGameObject,
                     public IInputListener,
                     public IDrawable {
public:
    explicit Player(const str& name) : IGameObject(name) {}
    void Draw(const Shared<SceneContext>& context) override;
    void Awake(const Shared<SceneContext>& context) override;
    void Update(const Shared<SceneContext>& context, f32 dT) override;
    void Destroyed(const Shared<SceneContext>& context) override;
    void OnMouseMove(const FMouseMoveEvent& event, const FInputMap& input) override;
    void OnKeyDown(const FKeyEvent& event, const FInputMap& input) override;

private:
    SpriteRenderer* mSprite = None;
    Transform* mTransform   = None;
    Weak<SceneContext> mContext;
};
