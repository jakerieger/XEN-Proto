// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "Camera.h"

OrthoCamera::OrthoCamera(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
    : mLeft(left), mRight(right), mBottom(bottom), mTop(top), mNear(near), mFar(far),
      mPosition(0.0f), mScale(1.0f) {
    Update();
}

void OrthoCamera::SetPosition(const glm::vec3& position) {
    mPosition = position;
    UpdateView();
}

void OrthoCamera::SetScale(f32 scale) {
    mScale = scale;
    UpdateProjection();
}

void OrthoCamera::SetBounds(f32 left, f32 right, f32 bottom, f32 top) {
    mLeft   = left;
    mRight  = right;
    mBottom = bottom;
    mTop    = top;
    UpdateProjection();
}

glm::mat4 OrthoCamera::GetViewMatrix() const {
    return mViewMatrix;
}

glm::mat4 OrthoCamera::GetProjectionMatrix() const {
    return mProjectionMatrix;
}

glm::vec3 OrthoCamera::ScreenToWorld(const glm::vec2& screenCoords,
                                     const glm::vec2& screenSize) const {
    const glm::vec4 ndc((screenCoords.x / screenSize.x) * 2.0f - 1.0f,
                        (screenCoords.y / screenSize.y) * 2.0f - 1.0f,
                        0.0f,
                        1.0f);

    const glm::vec4 world = glm::inverse(mProjectionMatrix * mViewMatrix) * ndc;
    return glm::vec3(world.x, world.y, world.z) / world.w;
}

glm::vec2 OrthoCamera::WorldToScreen(const glm::vec3& worldCoords,
                                     const glm::vec2& screenSize) const {
    glm::vec4 screen = mProjectionMatrix * mViewMatrix * glm::vec4(worldCoords, 1.0f);
    screen /= screen.w;

    return {(screen.x + 1.0f) * 0.5f * screenSize.x, (screen.y + 1.0f) * 0.5f * screenSize.y};
}

Rect OrthoCamera::GetViewport() const {
    return Rect(CAST<int>(mLeft), CAST<int>(mTop), CAST<int>(mRight), CAST<int>(mBottom));
}

void OrthoCamera::UpdateView() {
    mViewMatrix = glm::translate(glm::mat4(1.0f), -mPosition);
}

void OrthoCamera::UpdateProjection() {
    f32 width         = (mRight - mLeft) / mScale;
    f32 height        = (mTop - mBottom) / mScale;
    mProjectionMatrix = glm::ortho(mLeft, mRight, mBottom, mTop, mNear, mFar);
}

void OrthoCamera::Update() {
    UpdateView();
    UpdateProjection();
}

Shared<OrthoCamera> OrthoCamera::CreateDefault() {
    return std::make_shared<OrthoCamera>(-640, 640, -360, 360);
}