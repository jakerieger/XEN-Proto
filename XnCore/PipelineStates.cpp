// Author: Jake Rieger
// Created: 8/21/2024.
//

#include "PipelineStates.h"
#include <glad/glad.h>

void PipelineStates::SetDefaults() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
}

void PipelineStates::DrawSolid() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void PipelineStates::DrawWire() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}