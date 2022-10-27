#pragma once

#include "../Utility.h"
#include "EngineModelDataInterface.h" 

#ifndef GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif

struct RenderSlot
{
    ModelData Model;

    unsigned int NumAttributes = 0;

    const char* VertexShader = nullptr;
    const char* FragmentShader = nullptr;
    const char* Texture = nullptr;
    unsigned int TextureArrayIndex = 0;

    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix; 

    bool Draw = false; 

    bool DepthTest = false;
};

