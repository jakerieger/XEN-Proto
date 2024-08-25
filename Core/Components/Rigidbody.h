// Author: Jake Rieger
// Created: 8/25/2024.
//

#pragma once

#include "Core/Component.h"

class Rigidbody final : public IComponent {
public:
    void Awake() override;
    void Update() override;
    void Destroyed() override;

private:
    void LateUpdate() override {}
};
