#pragma once

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
#include <GL/gl.h>

GLuint setupCubemap()
{
    // Setup textures
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nChannels;
    GLubyte* data;
    const char* faceTextures [6] =
            {
                    "resources/right.jpg",
                    "resources/left.jpg",
                    "resources/top.jpg",
                    "resources/bottom.jpg",
                    "resources/front.jpg",
                    "resources/back.jpg"
            };

    for (GLubyte i = 0; i < 6; ++i)
    {
        data = stbi_load(faceTextures[i], &width, &height, &nChannels, 0);

        if (!data)
        {
            printf("Failed to load texture %s ", faceTextures[i]);
            stbi_image_free(data);
            continue;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0,
                     GL_RGB,
                     width,
                     height,
                     0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     data);

    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
