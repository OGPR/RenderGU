#pragma once

#include "../Utility.h"

struct RenderSlot
{
    void* models = nullptr;
    void* shaders = nullptr;
    void* textures = nullptr;

    float* Model = nullptr;
    unsigned int ModelIndices = 0; 
    const char* VertexShader = nullptr;
    const char* FragmentShader = nullptr;
    const char* Texture = nullptr;
    unsigned int TextureArrayIndex = 0;

    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix; 

    bool Draw = false; 
};
