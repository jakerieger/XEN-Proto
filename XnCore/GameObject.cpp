// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "GameObject.h"
#include "SceneContext.h"

void IGameObject::Destroy(const Shared<SceneContext>& context) {
    Destroyed(context);
    context->GameObjects.erase(mName);
}