// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "GameObject.h"
#include "Shared/Types.h"

class Scene {
public:
    Scene() = default;

    void Awake() const;
    void Update(f32 dT) const;
    void PhysicsUpdate() const;
    void LateUpdate() const;
    void Destroyed() const;
    void Render() const;

    [[nodiscard]] Vector<Shared<IGameObject>> GetGameObjects() const;

private:
    Vector<Shared<IGameObject>> mGameObjects;
};
