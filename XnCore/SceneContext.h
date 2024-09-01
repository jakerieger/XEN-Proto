// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Shared/Types.h"
#include "Camera.h"
#include "EventSystem.h"
#include "Events.h"
#include "GameObject.h"

#include <iostream>

class SceneContext {
public:
    SceneContext()  = default;
    ~SceneContext() = default;

    Dictionary<str, Shared<IGameObject>> GameObjects;
    Shared<ICamera> MainCamera;
    Shared<EventDispatcher> EventSystem;
};

template<typename T>
static Vector<T*> FindAllGameObjectsOf(const Shared<SceneContext>& context) {
    Vector<T*> gameObjects;
    for (auto& [name, obj] : context->GameObjects) {
        if (auto casted = DCAST<T*>(obj.get()); casted) {
            gameObjects.push_back(casted);
        }
    }

    return gameObjects;
}

template<typename T>
static T* FindGameObjectOf(const Shared<SceneContext>& context, const str& name) {
    for (auto& [name, obj] : context->GameObjects) {
        if (auto casted = DCAST<T*>(obj.get()); casted) {
            return casted;
        }
    }

    return nullptr;
}

template<typename T, typename... Args>
static void Instantiate(const str& name, const Shared<SceneContext>& context, Args&&... args) {
    Shared<T> go               = std::make_shared<T>(name, std::forward<Args>(args)...);
    context->GameObjects[name] = go;
    go->Awake(context);

    std::cout << "Instantiated game object\n";
}

static void PlaySound(const Shared<SceneContext>& context,
                      const str& name,
                      const Path& path,
                      f32 gain  = 0.5f,
                      bool loop = false) {
    const auto event = PlaySoundEvent(name, path, gain, loop);
    context->EventSystem->Dispatch(event);
}