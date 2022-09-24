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
    unsigned int IndexArraySize = 0;
    unsigned int VertexDataSize = 0;
    unsigned int Indices = 0;
    unsigned int VBOMemoryAllocationSize = 0;
    unsigned int VBOMemoryAllocationSize_PosOnly = 0;
    unsigned int EBOMemoryAllocationSize = 0;

    Attribute* AttributeArray = nullptr;

    
};
