#pragma once

#include "../Utility.h"
#include "EngineModelDataInterface.h" 

struct Attribute;

struct RenderSlot
{
    ModelData Model;

    Attribute* AttributeArray = nullptr;
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

struct Attribute
{
    unsigned int Size = 0;
    GLsizei Stride = 0;
    const void* Offset = 0;
};
