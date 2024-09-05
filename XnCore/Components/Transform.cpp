// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "Transform.h"

#include <rttr/type>
#include <rttr/registration_friend.h>
#include <rttr/registration.h>

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

Rect Transform::GetBounds() const {
    const auto left   = mPosition.x - mScale.x;
    const auto top    = mPosition.y - mScale.y;
    const auto right  = mPosition.x + mScale.x;
    const auto bottom = mPosition.y + mScale.y;

    return {CAST<i32>(left), CAST<i32>(top), CAST<i32>(right), CAST<i32>(bottom)};
}

bool Transform::IsColliding(const Rect& a, const Rect& b) {
    if (a.Right <= b.Left || b.Right <= a.Left) {
        return false;
    }

    if (a.Bottom <= b.Top || b.Bottom <= a.Top) {
        return false;
    }

    return true;
}

RTTR_REGISTRATION {
    using namespace rttr;

    registration::class_<Transform>("Transform")
      .constructor<>()
      .property("Position", &Transform::mPosition)
      .property("Rotation", &Transform::mRotation)
      .property("Scale", &Transform::mScale)
      .property("Matrix", &Transform::mMatrix)
      .method("Update", &Transform::Update)
      .method("GetBounds", &Transform::GetBounds)
      .method("IsColliding", &Transform::IsColliding);
}