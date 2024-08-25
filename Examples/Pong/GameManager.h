// Author: Jake Rieger
// Created: 8/25/2024.
//

#pragma once

#include "Core/GameObject.h"
#include "Core/GraphicsContext.h"

using namespace GameObject::Traits;

class GameManager final : public IGameObject,
                          public IInputListener {
public:
    explicit GameManager(GraphicsContext* context);

    void Awake(const Shared<SceneContext>& context) override;
    void Update(const Shared<SceneContext>& context, f32 dT) override;
    void LateUpdate(const Shared<SceneContext>& context) override;
    void Destroyed(const Shared<SceneContext>& context) override;

    void OnKeyDown(const FKeyEvent& event, const FInputMap& input) override;

    void PlayerScored();
    void OpponentScored();

private:
    GraphicsContext* mGraphicsContext = None;
    int mScorePlayer                  = 0;
    int mScoreOpponent                = 0;
    int mScoreToWin                   = 10;
};
