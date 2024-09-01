// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "GameObject.h"
#include "SceneContext.h"
#include "Shared/Types.h"

class Scene {
public:
    explicit Scene(const Shared<EventDispatcher>& eventDispatcher);

    void Awake() const;
    void Update(f32 dT) const;
    void PhysicsUpdate() const;
    void LateUpdate() const;
    void Destroyed() const;
    void Render() const;

    [[nodiscard]] Dictionary<str, Shared<IGameObject>> GetGameObjects() const;

    template<typename T>
    void AddGameObject(const Shared<T>& gameObject) {
        static_assert(std::is_base_of_v<IGameObject, T>, "T must derive from IGameObject");
        mSceneContext->GameObjects[gameObject->GetName()] = gameObject;
    }

    void SetCamera(const Shared<ICamera>& camera) const;
    [[nodiscard]] Shared<ICamera> GetCamera() const;

    template<typename T>
    T* GetCameraAs() {
        return DCAST<T*>(GetCamera().get());
    }

private:
    Shared<SceneContext> mSceneContext;
};
