#pragma once

static const auto Sprite_VS = R""(
#version 460 core
layout (location = 0) in vec4 aVertex;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vec2 TexCoord;

void main() {
    vec2 position = aVertex.xy;
    vec2 texCoord = aVertex.zw;

    gl_Position = uProjection * uView * uModel * vec4(position, 0.0, 1.0);
    TexCoord = texCoord;
}
)"";

static const auto Sprite_FS = R""(
#version 460 core
 out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D uSprite;

void main() {
    FragColor = texture(uSprite, TexCoord);
}
)"";