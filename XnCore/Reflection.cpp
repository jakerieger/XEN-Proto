// Author: Jake Rieger
// Created: 9/5/2024.
//

#pragma once

#include "Components/Transform.h"

#include <rttr/type>
#include <rttr/registration_friend.h>
#include <rttr/registration.h>

#include "XnCore/Scene.h"
#include "XnCore/GameObject.h"
#include "XnCore/Component.h"

// TODO: Split this in to multiple TUs
RTTR_REGISTRATION {
    using namespace rttr;

    registration::class_<Scene>("Scene")(policy::ctor::as_std_shared_ptr)
      .constructor<Shared<EventDispatcher>&>()
      .property("SceneContext", &Scene::mSceneContext, registration::private_access);

    registration::class_<IGameObject>("IGameObject")
      .constructor<str>()(policy::ctor::as_std_shared_ptr)
      .property("Name", &IGameObject::mName, registration::protected_access)(
        metadata("TOOL_TIP", "Set the name of the GameObject."))
      .property_readonly("Components", &IGameObject::GetComponentsRaw)
      .method("Awake", &IGameObject::Awake)
      .method("Update", &IGameObject::Update)
      .method("LateUpdate", &IGameObject::LateUpdate)
      .method("Destroyed", &IGameObject::Destroyed);

    registration::class_<IComponent>("IComponent")
      .method("Awake", &IComponent::Awake)
      .method("Update", &IComponent::Update)
      .method("LateUpdate", &IComponent::LateUpdate)
      .method("Destroyed", &IComponent::Destroyed);

    registration::class_<Transform>("Transform")
      .constructor<>()
      .property("Position", &Transform::mPosition)
      .property("Rotation", &Transform::mRotation)
      .property("Scale", &Transform::mScale)
      .property("Matrix", &Transform::mMatrix)
      .method("Update", &Transform::Update)
      .method("GetBounds", &Transform::GetBounds)
      .method("IsColliding", &Transform::IsColliding);
}