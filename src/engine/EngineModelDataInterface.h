#pragma once

struct Attribute
{
    unsigned int Size = 0;
    GLsizei Stride = 0;
    const void* Offset = 0;
};

struct ModelData
{
    float* VertexData = nullptr;
    unsigned int* IndexArray = nullptr; 
    unsigned int Indices = 0;
    unsigned int VBOMemoryAllocationSize = 0;
    unsigned int EBOMemoryAllocationSize = 0;

    const char* Name = nullptr;

    Attribute* AttributeArray = nullptr;
};
