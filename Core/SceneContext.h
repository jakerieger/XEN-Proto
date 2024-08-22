// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Camera.h"
#include "GameObject.h"
#include "Shared/Types.h"

using namespace GameObject::Traits;

class SceneContext {
public:
    SceneContext()  = default;
    ~SceneContext() = default;

    Vector<Shared<IGameObject>> GameObjects;
    Shared<ICamera> MainCamera;
};

#define ASSERT_GAMEOBJECT                                                                          \
    static_assert(std::is_base_of_v<IGameObject, T> || std::is_base_of_v<IPhysicsObject, T> ||     \
                    std::is_base_of_v<IInputListener, T> || std::is_base_of_v<IDrawable, T>,       \
                  "T must be a subclass of IGameObject or any of its traits.")

template<typename T>
static Vector<T*> FindAllGameObjectsOf(const Shared<SceneContext>& context) {
    ASSERT_GAMEOBJECT;
    Vector<T*> gameObjects;
    for (auto& go : context->GameObjects) {
        if (auto casted = DCAST<T*>(go.get()); casted) {
            gameObjects.push_back(casted);
        }
    }

    return gameObjects;
}

template<typename T>
static T* FindGameObjectOf(const Shared<SceneContext>& context, const str& name) {
    ASSERT_GAMEOBJECT;
    for (auto& go : context->GameObjects) {
        if (auto casted = dynamic_cast<T*>(go.get()); casted && casted->GetName() == name) {
            return casted;
        }
    }

    return nullptr;
}