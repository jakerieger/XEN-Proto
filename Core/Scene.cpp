// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "Scene.h"

using namespace GameObject::Traits;

Scene::Scene() {
    mSceneContext = std::make_shared<SceneContext>();
};

void Scene::Awake() const {
    // TODO: Pass screen dimensions to scene class, or something idfk
    mSceneContext->MainCamera = std::make_shared<OrthoCamera>(1280.f, 720.f);

    for (const auto& go : mSceneContext->GameObjects) {
        go->Awake(mSceneContext);
    }
}

void Scene::Update(f32 dT) const {
    for (const auto& go : mSceneContext->GameObjects) {
        go->Update(mSceneContext, dT);
    }
}

void Scene::PhysicsUpdate() const {
    for (const auto& go : FindAllGameObjectsOf<IPhysicsObject>(mSceneContext)) {
        go->PhysicsUpdate(mSceneContext);
    }
}

void Scene::LateUpdate() const {
    for (const auto& go : mSceneContext->GameObjects) {
        go->LateUpdate(mSceneContext);
    }
}

void Scene::Destroyed() const {
    for (const auto& go : mSceneContext->GameObjects) {
        go->Destroyed(mSceneContext);
    }

    mSceneContext->MainCamera.reset();
}

void Scene::Render() const {
    for (const auto& go : FindAllGameObjectsOf<IDrawable>(mSceneContext)) {
        go->Draw(mSceneContext);
    }
}

Vector<Shared<IGameObject>> Scene::GetGameObjects() const {
    return mSceneContext->GameObjects;
}