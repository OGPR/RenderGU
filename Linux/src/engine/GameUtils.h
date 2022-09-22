#pragma once

#include "../Utility.h"

struct Attribute;

struct RenderSlot
{
    void* shaders = nullptr;
    void* textures = nullptr;

    float* Model = nullptr;
    unsigned int ModelIndices = 0;

    Attribute* AttributeArray = nullptr;
    unsigned int NumAttributes = 0;

    unsigned int VBOMemoryAllocationSize = 0;
    unsigned int* IndexArray = nullptr;
    unsigned int EBOMemoryAllocationSize = 0;


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
