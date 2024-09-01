// Author: Jake Rieger
// Created: 8/22/2024.
//

#include "TextureLoader.h"

#include <stb_image.h>
#include <glad/glad.h>

u32 LoadTextureFromFile(const Path& file, u32& outWidth, u32& outHeight) {
    if (!FileSystem::exists(file)) {
        throw RuntimeError("File not found");
    }

    u32 id;
    glGenTextures(1, &id);

    i32 width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    u8* data = stbi_load(file.string().c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        outWidth      = width;
        outHeight     = height;
        GLenum format = GL_RGB;
        if (nrComponents == 1) {
            format = GL_RED;
        } else if (nrComponents == 3) {
            format = GL_RGB;
        } else if (nrComponents == 4) {
            format = GL_RGBA;
        }

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     CAST<int>(format),
                     width,
                     height,
                     0,
                     format,
                     GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_S,
                        format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_WRAP_T,
                        format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
    } else {
        stbi_image_free(data);
    }

    return id;
}