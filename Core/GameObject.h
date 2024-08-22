// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Shared/Types.h"

class SceneContext;

class IGameObject {
public:
    virtual ~IGameObject() = default;

    virtual void Awake(const Shared<SceneContext>& context)          = 0;
    virtual void Update(const Shared<SceneContext>& context, f32 dT) = 0;
    virtual void LateUpdate(const Shared<SceneContext>& context)     = 0;
    virtual void Destroyed(const Shared<SceneContext>& context)      = 0;

    template<typename T>
    T* As() {
        return DCAST<T*>(this);
    }

protected:
};

namespace GameObject::Traits {
    class IPhysicsObject {
    public:
        virtual ~IPhysicsObject()                                       = default;
        virtual void PhysicsUpdate(const Shared<SceneContext>& context) = 0;
    };

    class IInputListener {
    public:
        virtual ~IInputListener() = default;
        virtual void OnKey() {}
        virtual void OnKeyDown() {}
        virtual void OnKeyUp() {}
        virtual void OnMouseMove() {}
        virtual void OnMouseDown() {}
        virtual void OnMouseUp() {}
        virtual void OnMouseWheel() {}
        virtual void OnMouseLeave() {}
        virtual void OnMouseEnter() {}
    };

    class IDrawable {
    public:
        virtual ~IDrawable()                                   = default;
        virtual void Draw(const Shared<SceneContext>& context) = 0;
    };
}  // namespace GameObject::Traits