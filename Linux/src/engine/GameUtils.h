#pragma once

#include "../Utility.h"

struct Slot
{
    void* models;
    void* shaders;
    void* textures;

    float* Model;
    unsigned int ModelIndices = 0; 
    const char* VertexShader = nullptr;
    const char* FragmentShader = nullptr;
    const char* Texture = nullptr;

    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix; 

    bool Draw = false; 
};
