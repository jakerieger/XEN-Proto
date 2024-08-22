// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "Shared/Types.h"
#include "Core/Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform final : public IComponent {
public:
    Transform() = default;

    void Awake() override;
    void Update() override;
    void LateUpdate() override;
    void Destroyed() override;

    [[nodiscard]] glm::mat4 GetModelMatrix() const;
    [[nodiscard]] glm::vec2 GetPosition() const;
    [[nodiscard]] glm::vec2 GetRotation() const;
    [[nodiscard]] glm::vec2 GetScale() const;

    void SetPosition(glm::vec2 position);
    void SetRotation(glm::vec2 rotation);
    void SetScale(glm::vec2 scale);

private:
    glm::mat4 mMatrix   = {1.f};
    glm::vec2 mPosition = {0.f, 0.f};
    glm::vec2 mRotation = {0.f, 0.f};
    glm::vec2 mScale    = {1.f, 1.f};
};
