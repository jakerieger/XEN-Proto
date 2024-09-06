// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

/// @brief Component interface used for implementing game object components.
///
/// Provides the core lifecycle hooks for game objects.
class IComponent {
public:
    virtual ~IComponent() = default;

    /// @brief This is called when the game object is first spawned.
    virtual void Awake() = 0;

    /// @brief This is called one per frame right before the scene is rendered.
    virtual void Update() = 0;

    /// @brief This is called one per frame after the scene has been rendered.
    virtual void LateUpdate() = 0;

    /// @brief This is called when the game object is despawned.
    virtual void Destroyed() = 0;
};