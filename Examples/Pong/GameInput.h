// Author: Jake Rieger
// Created: 8/25/2024.
//

#pragma once

#include "Core/GameObject.h"
#include "Core/GraphicsContext.h"

using namespace GameObject::Traits;

class GameInput final : public IGameObject,
                        public IInputListener {
public:
    explicit GameInput(GraphicsContext* context);

    void Awake(const Shared<SceneContext>& context) override;
    void Update(const Shared<SceneContext>& context, f32 dT) override;
    void LateUpdate(const Shared<SceneContext>& context) override;
    void Destroyed(const Shared<SceneContext>& context) override;

    void OnKeyDown(const FKeyEvent& event, const FInputMap& input) override;

private:
    GraphicsContext* mGraphicsContext = None;
};
