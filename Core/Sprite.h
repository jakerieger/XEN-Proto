// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "Shader.h"
#include "Shared/Types.h"

#include <glm/glm.hpp>

class Sprite {
public:
    explicit Sprite(const Path& sprite);
    ~Sprite();
    void Draw(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& model) const;

    [[nodiscard]] glm::mat4 GetModel() const {
        return mModel;
    }

private:
    u32 mTexture;
    u32 mVBO {};
    u32 mVAO {};
    Unique<Shader> mShader;
    glm::mat4 mModel;
};
