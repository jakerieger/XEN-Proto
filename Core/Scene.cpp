// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Scene.h"

void Scene::Awake() const {
    for (const auto& go : mGameObjects) {
        go->Awake();
    }
}

void Scene::Update(f32 dT) const {
    for (const auto& go : mGameObjects) {
        go->Update(dT);
    }
}

void Scene::PhysicsUpdate() const {
    for (const auto& go : mGameObjects) {
        go->PhysicsUpdate();
    }
}

void Scene::LateUpdate() const {
    for (const auto& go : mGameObjects) {
        go->LateUpdate();
    }
}

void Scene::Destroyed() const {
    for (const auto& go : mGameObjects) {
        go->Destroyed();
    }
}

void Scene::Render() const {
    for (const auto& go : mGameObjects) {
        go->Render();
    }
}

Vector<Shared<IGameObject>> Scene::GetGameObjects() const {
    return mGameObjects;
}