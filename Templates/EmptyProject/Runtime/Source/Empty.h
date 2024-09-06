// Author: Jake Rieger
// Created: 9/5/2024.
//

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define CORE_API __declspec(dllexport)

class CORE_API Empty {
public:
    explicit Empty(GLFWwindow* context);

    void Render() const;

private:
    GLFWwindow* mContext;
};
