// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "../Shader.h"
#include "../../Shared/Types.h"
#include "Transform.h"
#include "../Component.h"

#include <glm/glm.hpp>

class SpriteRenderer final : public IComponent {
public:
    SpriteRenderer(const Path& sprite, Transform* transform);
    ~SpriteRenderer() override;
    void Draw(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& model) const;

    void Awake() override;
    void Update() override;
    void LateUpdate() override;
    void Destroyed() override;

private:
    u32 mTexture;
    u32 mVBO {};
    u32 mVAO {};
    Unique<Shader> mShader;
};
