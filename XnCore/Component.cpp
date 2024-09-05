// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "Component.h"

#include <rttr/type>
#include <rttr/registration_friend.h>
#include <rttr/registration.h>

RTTR_REGISTRATION {
    using namespace rttr;

    registration::class_<IComponent>("IComponent")
      .method("Awake", &IComponent::Awake)
      .method("Update", &IComponent::Update)
      .method("LateUpdate", &IComponent::LateUpdate)
      .method("Destroyed", &IComponent::Destroyed);
}