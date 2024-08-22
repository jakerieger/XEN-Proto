// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "Shared/Types.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

class ICamera {
public:
    virtual ~ICamera() = default;

    [[nodiscard]] virtual glm::mat4 GetViewMatrix() const       = 0;
    [[nodiscard]] virtual glm::mat4 GetProjectionMatrix() const = 0;
    virtual void Update() = 0;

    template<typename T>
    T* As() {
        return DCAST<T*>(this);
    }
};

class OrthoCamera final : public ICamera {
public:
    OrthoCamera(
      float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);

    void SetPosition(const glm::vec3& position);
    void SetScale(float scale);
    void SetBounds(float left, float right, float bottom, float top);

    [[nodiscard]] glm::mat4 GetViewMatrix() const override;
    [[nodiscard]] glm::mat4 GetProjectionMatrix() const override;
    [[nodiscard]] glm::vec3 ScreenToWorld(const glm::vec2& screenCoords, const glm::vec2& screenSize) const;
    [[nodiscard]] glm::vec2 WorldToScreen(const glm::vec3& worldCoords, const glm::vec2& screenSize) const;

    void Update() override;

    static Shared<OrthoCamera> CreateDefault();

private:
    void UpdateView();
    void UpdateProjection();

    glm::mat4 mViewMatrix{};
    glm::mat4 mProjectionMatrix{};

    f32 mLeft, mRight, mBottom, mTop, mNear, mFar;
    glm::vec3 mPosition;
    f32 mScale;
};