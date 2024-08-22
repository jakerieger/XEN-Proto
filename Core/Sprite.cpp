// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "Sprite.h"
#include "Primitives.h"
#include "TextureLoader.h"

#include <glad/glad.h>

#pragma region Shaders
#include "Shaders/SpriteQuad.h"

#include <glm/ext/matrix_transform.hpp>
#pragma endregion

Sprite::Sprite(const Path& sprite) {
    u32 width;
    u32 height;
    mTexture = LoadTextureFromFile(sprite, width, height);
    mShader  = std::make_unique<Shader>(Sprite_VS, Sprite_FS);

    mModel                    = glm::mat4(1.0f);
    const f32 aspect          = (f32)width / (f32)height;
    constexpr f32 targetWidth = 1.f;
    const f32 targetHeight    = targetWidth / aspect;
    mModel                    = glm::translate(mModel, glm::vec3(-25, 12, 0));
    mModel                    = glm::scale(mModel, glm::vec3(targetWidth, targetHeight, 1.0f));

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

Sprite::~Sprite() {
    mShader.reset();
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
    glDeleteTextures(1, &mTexture);
}

void Sprite::Draw(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& model) const {
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