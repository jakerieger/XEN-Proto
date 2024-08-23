// Author: Jake Rieger
// Created: 8/22/2024.
//

#pragma once

#include "GameObject.h"
#include "Shared/Types.h"

#include <GLFW/glfw3.h>

using GameObject::Traits::IInputListener;

struct FActionState {
    bool Pressed  = false;
    bool Released = false;
};

class InputManager {
public:
    InputManager(GLFWwindow* window, FInputMap inputMap);
    ~InputManager();

    void RegisterListener(const Shared<IInputListener>& listener);
    void UnregisterListener(const Shared<IInputListener>& listener);
    void SetShouldDispatch(bool dispatch);
    [[nodiscard]] bool ShouldDispatch() const;

    [[nodiscard]] Vector<Shared<IInputListener>> GetListeners() const;
    void UpdateKeyStates(u32 key, FActionState state);
    void UpdateMouseButtonStates(u32 button, FActionState state);
    [[nodiscard]] FActionState GetKeyState(u32 key) const;
    [[nodiscard]] FActionState GetMouseButtonState(u32 button) const;
    [[nodiscard]] Dictionary<u32, FActionState> GetKeyStates() const;
    [[nodiscard]] Dictionary<u32, FActionState> GetMouseButtonStates() const;

    FInputMap GetInputMap() const;

private:
    Vector<Shared<IInputListener>> mListeners;
    Dictionary<u32, FActionState> mKeyStates;
    Dictionary<u32, FActionState> mMouseButtonStates;
    Thread mDispatchThread;
    bool mShouldDispatch = false;
    FInputMap mInputMap;
};
