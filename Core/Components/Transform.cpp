// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "Transform.h"

void Transform::Awake() {}

void Transform::Update() {
    glm::mat4 matrix = {1.f};
    matrix           = glm::translate(matrix, glm::vec3(mPosition.x, mPosition.y, 0.0f));
    matrix           = glm::rotate(matrix, glm::radians(mRotation.x), glm::vec3(1, 0, 0));
    matrix           = glm::rotate(matrix, glm::radians(mRotation.y), glm::vec3(0, 1, 0));
    matrix           = glm::scale(matrix, glm::vec3(mScale.x, mScale.y, 1.0f));
    mMatrix          = matrix;
}

void Transform::LateUpdate() {}

void Transform::Destroyed() {}

glm::mat4 Transform::GetModelMatrix() const {
    return mMatrix;
}

glm::vec2 Transform::GetPosition() const {
    return mPosition;
}

glm::vec2 Transform::GetRotation() const {
    return mRotation;
}

glm::vec2 Transform::GetScale() const {
    return mScale;
}

void Transform::SetPosition(const glm::vec2 position) {
    mPosition = position;
}

void Transform::SetRotation(const glm::vec2 rotation) {
    mRotation = rotation;
}

void Transform::SetScale(const glm::vec2 scale) {
    mScale = scale;
}