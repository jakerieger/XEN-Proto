// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "SpriteRenderer.h"
#include "../Primitives.h"
#include "../TextureLoader.h"

#include <../../Shared/Vendor/glad/glad.h>

#pragma region Shaders
#include "../../Shaders/SpriteQuad.h"

#include <glm/ext/matrix_transform.hpp>
#pragma endregion

SpriteRenderer::SpriteRenderer(const Path& sprite, Transform* transform, const glm::vec2& scale) {
    u32 width;
    u32 height;
    mTexture = LoadTextureFromFile(sprite, width, height);
    mShader  = std::make_unique<Shader>(Sprite_VS, Sprite_FS);

    transform->SetScale({CAST<f32>(width) / 4.f, CAST<f32>(height) / 4.f});
    transform->SetScale(transform->GetScale() * scale);

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER,
                 Primitives::Quad.size() * sizeof(f32),
                 Primitives::Quad.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(f32), CAST<void*>(None));

    mShader->Bind();
    mShader->SetInt("uSprite", 0);
    mShader->Unbind();
}

SpriteRenderer::~SpriteRenderer() {
    mShader.reset();
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteTextures(1, &mTexture);
}

void SpriteRenderer::Draw(const glm::mat4& view,
                          const glm::mat4& proj,
                          const glm::mat4& model) const {
    mShader->Bind();
    mShader->SetMat4("uView", view);
    mShader->SetMat4("uProjection", proj);
    mShader->SetMat4("uModel", model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture);

    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void SpriteRenderer::Awake() {}

void SpriteRenderer::Update() {}

void SpriteRenderer::LateUpdate() {}

void SpriteRenderer::Destroyed() {}