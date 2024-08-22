// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

class IComponent {
public:
    virtual ~IComponent() = default;

    virtual void Awake() = 0;
    virtual void Update() = 0;
    virtual void LateUpdate() = 0;
    virtual void Destroyed() = 0;
};
