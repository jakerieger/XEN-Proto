// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Shared/Types.h"

class IGameObject {
public:
    virtual ~IGameObject() = default;

    virtual void Awake()         = 0;
    virtual void Update(f32 dT)  = 0;
    virtual void PhysicsUpdate() = 0;
    virtual void LateUpdate()    = 0;
    virtual void Destroyed()     = 0;

    virtual void Render() = 0;

protected:
};
