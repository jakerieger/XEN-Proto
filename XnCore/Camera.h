// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "Shared/Types.h"

#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>

/// @brief Base interface for implementing cameras.
///
/// In XEN, cameras are simply objects that return a view matrix
/// and projection matrix. They can have world positions if needed,
/// but it is not a requirement. All game objects receive a reference
/// to the main camera that is set for that scene.
class ICamera {
public:
    virtual ~ICamera() = default;

    /// @brief Returns the camera's view matrix.
    [[nodiscard]] virtual glm::mat4 GetViewMatrix() const = 0;

    /// @brief Returns the camera's projection matrix.
    [[nodiscard]] virtual glm::mat4 GetProjectionMatrix() const = 0;

    /// @brief Provides a generic update method for updating camera properties.
    virtual void Update() = 0;

    /// @brief Casts down an ICamera to its inheriting class T.
    /// @returns Pointer to T or nullptr if cast fails.
    ///
    /// Example:
    /// @code
    /// ICamera* baseCam;
    /// baseCam->As<OrthoCamera>()->SomeOrthoCameraMethod();
    /// @endcode
    template<typename T>
    T* As() {
        return DCAST<T*>(this);
    }
};

/// @brief Implements a basic orthographic camera.
class OrthoCamera final : public ICamera {
public:
    OrthoCamera(float width, float height, float near = -1.0f, float far = 1.0f);

    /// @breif Sets camera's world position.
    void SetPosition(const glm::vec3& position);

    /// @brief Sets the camera's viewport scale.
    void SetScale(float scale);

    /// @brief Sets the camera's viewport bounds.
    void SetBounds(float left, float right, float bottom, float top);

    [[nodiscard]] glm::mat4 GetViewMatrix() const override;
    [[nodiscard]] glm::mat4 GetProjectionMatrix() const override;

    /// @brief Converts a screen coordinate to the camera's viewport coordinates.
    [[nodiscard]] glm::vec3 ScreenToWorld(const glm::vec2& screenCoords,
                                          const glm::vec2& screenSize) const;

    /// @brief Converts a viewport coordinate to screen coordinates.
    [[nodiscard]] glm::vec2 WorldToScreen(const glm::vec3& worldCoords,
                                          const glm::vec2& screenSize) const;

    /// @brief Returns viewport bounds.
    [[nodiscard]] Rect GetViewport() const;

    void Update() override;

    void ResizeViewport(float width, float height);

    /// @brief Creates a default OrthoCamera instance.
    static Shared<OrthoCamera> CreateDefault();

private:
    void UpdateView();
    void UpdateProjection();

    glm::mat4 mViewMatrix {};
    glm::mat4 mProjectionMatrix {};

    f32 mLeft;
    f32 mRight;
    f32 mBottom;
    f32 mTop;
    f32 mNear;
    f32 mFar;
    f32 mScale;
    glm::vec3 mPosition;
    f32 mAspect = 16.f / 9.f;
};