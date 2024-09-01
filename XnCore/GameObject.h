// Author: Jake Rieger
// Created: 8/21/2024.
//

#pragma once

#include "Component.h"
#include "Config.h"
#include "Shared/Types.h"
#include "InputEvents.h"

// Forward declarations
class SceneContext;

class IGameObject {
public:
    virtual ~IGameObject() = default;

    virtual void Awake(const Shared<SceneContext>& context) {
        for (const auto& component : mComponents) {
            component->Awake();
        }
    }

    virtual void Update(const Shared<SceneContext>& context, f32 dT) {
        for (const auto& component : mComponents) {
            component->Update();
        }
    }

    virtual void LateUpdate(const Shared<SceneContext>& context) {
        for (const auto& component : mComponents) {
            component->LateUpdate();
        }
    }

    virtual void Destroyed(const Shared<SceneContext>& context) {
        for (const auto& component : mComponents) {
            component->Destroyed();
        }

        mComponents.clear();
    }

    template<typename T>
    T* As() {
        return DCAST<T*>(this);
    }

    template<typename T>
    T* GetComponent() {
        for (auto& components : mComponents) {
            if (auto casted = DCAST<T*>(components.get())) {
                return casted;
            }
        }

        return None;
    }

    Vector<Unique<IComponent>>& GetComponents() {
        return mComponents;
    }

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        auto component  = std::make_unique<T>(std::forward<Args>(args)...);
        T* componentPtr = component.get();
        mComponents.emplace_back(std::move(component));
        return componentPtr;
    }

protected:
    Vector<Unique<IComponent>> mComponents;
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
        virtual void OnKey(const FKeyEvent& event, const FInputMap& input) {}
        virtual void OnKeyDown(const FKeyEvent& event, const FInputMap& input) {}
        virtual void OnKeyUp(const FKeyEvent& event, const FInputMap& input) {}
        virtual void OnMouseMove(const FMouseMoveEvent& event, const FInputMap& input) {}
        virtual void OnMouseDown(const FMouseButtonEvent& event, const FInputMap& input) {}
        virtual void OnMouseUp(const FMouseButtonEvent& event, const FInputMap& input) {}
        virtual void OnMouseWheel(const FMouseWheelEvent& event, const FInputMap& input) {}
        virtual void OnMouseLeave(const FMouseMoveEvent& event, const FInputMap& input) {}
        virtual void OnMouseEnter(const FMouseMoveEvent& event, const FInputMap& input) {}
    };

    class IDrawable {
    public:
        virtual ~IDrawable()                                   = default;
        virtual void Draw(const Shared<SceneContext>& context) = 0;
    };
}  // namespace GameObject::Traits