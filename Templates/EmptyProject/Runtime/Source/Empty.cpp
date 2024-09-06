// Author: Jake Rieger
// Created: 9/5/2024.
//

#include "Empty.h"
#include "Shared/Types.h"

Empty::Empty(GLFWwindow* context) {
    mContext = context;

    glfwMakeContextCurrent(mContext);
    if (!gladLoadGLLoader(RCAST<GLADloadproc>(glfwGetProcAddress))) {
        glfwTerminate();
        throw RuntimeError("Failed to initialize GLAD");
    }
}

void Empty::Render() const {
    if (!mContext) {
        return;
    }

    glClearColor(15.f / 255.f, 16.f / 255.f, 28.f / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}