// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "Camera.h"

glm::mat4 OrthoCamera::GetViewMatrix() const {
    return glm::mat4(1.f);
}

glm::mat4 OrthoCamera::GetProjectionMatrix() const {
    const f32 w       = mWidth;
    const f32 h       = mHeight;
    const float ratio = w / h;
    glm::vec2 extents(ratio * 25.0f, 25.0f);
    extents *= mZoom;

    const glm::vec2 lower = mCenter - extents;
    const glm::vec2 upper = mCenter + extents;

    // X Axis vector
    const glm::vec4 x = {2.0f / (upper.x - lower.x), 0.f, 0.f, 0.f};
    // Y Axis vector
    const glm::vec4 y = {0.f, 2.0f / (upper.y - lower.y), 0.f, 0.f};
    // Z Axis Vector
    constexpr glm::vec4 z = {0.f, 0.f, 1.0f, 0.f};
    // Zoom(??) vector
    const glm::vec4 zm = {-(upper.x + lower.x) / (upper.x - lower.x),
                          -(upper.y + lower.y) / (upper.y - lower.y),
                          0.f,  // z bias
                          1.f};

    glm::mat4 m(1.f);
    m[0] = x;
    m[1] = y;
    m[2] = z;
    m[3] = zm;

    return m;
}

void OrthoCamera::ResetView() {
    mCenter = {0.f, 25.f};
    mZoom   = 1.0f;
}

glm::vec2 OrthoCamera::ScreenToWorld(const glm::vec2& point) const {
    const f32 u = point.x / mWidth;
    const f32 v = (mHeight - point.y) / mHeight;

    const f32 ratio = mWidth / mHeight;
    glm::vec2 extents(ratio * 25.0f, 25.0f);
    extents *= mZoom;

    const glm::vec2 lower = mCenter - extents;
    const glm::vec2 upper = mCenter + extents;

    glm::vec2 pw;
    pw.x = (1.0f - u) * lower.x + u * upper.x;
    pw.y = (1.0f - v) * lower.y + v * upper.y;
    return pw;
}

glm::vec2 OrthoCamera::WorldToScreen(const glm::vec2& point) const {
    const f32 ratio = mWidth / mHeight;
    glm::vec2 extents(ratio * 25.0f, 25.0f);
    extents *= mZoom;

    const glm::vec2 lower = mCenter - extents;
    const glm::vec2 upper = mCenter + extents;

    const float u = (point.x - lower.x) / (upper.x - lower.x);
    const float v = (point.y - lower.y) / (upper.y - lower.y);

    glm::vec2 ps;
    ps.x = u * mWidth;
    ps.y = (1.0f - v) * mHeight;
    return ps;
}