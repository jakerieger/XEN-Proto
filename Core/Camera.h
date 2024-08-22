// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "Shared/Types.h"

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

class ICamera {
public:
    virtual ~ICamera() = default;

    [[nodiscard]] virtual glm::mat4 GetViewMatrix() const       = 0;
    [[nodiscard]] virtual glm::mat4 GetProjectionMatrix() const = 0;

    template<typename T>
    T* As() {
        return DCAST<T*>(this);
    }
};

class OrthoCamera final : public ICamera {
public:
    OrthoCamera(float width, float height, float zoom = 1.f)
        : mZoom(zoom), mWidth(width), mHeight(height) {}
    [[nodiscard]] glm::mat4 GetViewMatrix() const override;
    [[nodiscard]] glm::mat4 GetProjectionMatrix() const override;

    void ResetView();

    [[nodiscard]] glm::vec2 ScreenToWorld(const glm::vec2& point) const;
    [[nodiscard]] glm::vec2 WorldToScreen(const glm::vec2& point) const;

private:
    glm::vec2 mCenter = {};
    f32 mZoom         = 1.f;
    f32 mWidth        = 0.f;
    f32 mHeight       = 0.f;
};