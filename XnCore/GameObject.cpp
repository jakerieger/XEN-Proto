// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "GameObject.h"
#include "SceneContext.h"

#include <rttr/type>
#include <rttr/registration_friend.h>
#include <rttr/registration.h>

void IGameObject::Destroy(const Shared<SceneContext>& context) {
    Destroyed(context);
    context->GameObjects.erase(mName);
}

RTTR_REGISTRATION {
    using namespace rttr;

    registration::class_<IGameObject>("IGameObject")
      .constructor<str>()(policy::ctor::as_std_shared_ptr)
      .property("Name", &IGameObject::mName, registration::protected_access)(
        metadata("TOOL_TIP", "Set the name of the GameObject."))
      .property_readonly("Components", &IGameObject::GetComponentsRaw)
      .method("Awake", &IGameObject::Awake)
      .method("Update", &IGameObject::Update)
      .method("LateUpdate", &IGameObject::LateUpdate)
      .method("Destroyed", &IGameObject::Destroyed);
}