// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "InputManager.h"

#include <utility>

static InputManager* gActiveManager = None;

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_F12 && action == GLFW_PRESS) {
    }

    if (!gActiveManager) {
        return;
    }

    const FKeyEvent event {key};
    if (action == GLFW_PRESS) {
        gActiveManager->UpdateKeyStates(key, {true, false});
        for (const auto& listener : gActiveManager->GetListeners()) {
            listener->OnKeyDown(event, gActiveManager->GetInputMap());
        }
    } else if (action == GLFW_RELEASE) {
        gActiveManager->UpdateKeyStates(key, {false, true});
        for (const auto& listener : gActiveManager->GetListeners()) {
            listener->OnKeyUp(event, gActiveManager->GetInputMap());
        }
    }
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {}

static void MouseMoveCallback(GLFWwindow* window, double x, double y) {}

static void ScrollCallback(GLFWwindow* window, double x, double y) {}

static void DispatchThread() {
    while (gActiveManager->ShouldDispatch()) {
        for (const auto& [key, state] : gActiveManager->GetKeyStates()) {
            if (state.Pressed) {
                FKeyEvent event {CAST<int>(key)};
                for (const auto& listener : gActiveManager->GetListeners()) {
                    listener->OnKey(event, gActiveManager->GetInputMap());
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }
}

InputManager::InputManager(GLFWwindow* window, FInputMap inputMap)
    : mInputMap(std::move(inputMap)) {
    gActiveManager = this;

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, MouseMoveCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    mDispatchThread = Thread(DispatchThread);
}

InputManager::~InputManager() {
    mShouldDispatch = false;
    mDispatchThread.join();
}

void InputManager::RegisterListener(const Shared<IInputListener>& listener) {
    if (listener) {
        mListeners.push_back(listener);
    }
}

void InputManager::UnregisterListener(const Shared<IInputListener>& listener) {}

void InputManager::SetShouldDispatch(const bool dispatch) {
    mShouldDispatch = dispatch;
}

bool InputManager::ShouldDispatch() const {
    return mShouldDispatch;
}

Vector<Shared<IInputListener>> InputManager::GetListeners() const {
    return mListeners;
}

void InputManager::UpdateKeyStates(const u32 key, const FActionState state) {
    mKeyStates[key] = state;
}

void InputManager::UpdateMouseButtonStates(const u32 button, const FActionState state) {
    mMouseButtonStates[button] = state;
}

FActionState InputManager::GetKeyState(const u32 key) const {
    return mKeyStates.find(key)->second;
}

FActionState InputManager::GetMouseButtonState(const u32 button) const {
    return mMouseButtonStates.find(button)->second;
}

Dictionary<u32, FActionState> InputManager::GetKeyStates() const {
    return mKeyStates;
}

Dictionary<u32, FActionState> InputManager::GetMouseButtonStates() const {
    return mMouseButtonStates;
}

FInputMap InputManager::GetInputMap() const {
    return mInputMap;
}