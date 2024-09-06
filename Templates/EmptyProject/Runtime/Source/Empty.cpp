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

    glClearColor(150.f / 255.f, 160.f / 255.f, 280.f / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}