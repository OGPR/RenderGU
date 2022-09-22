#pragma once

struct ModelData
{
    float* VertexData = nullptr;
    unsigned int* IndexArray = nullptr; 
    unsigned int IndexArraySize = 0;
    unsigned int VertexDataSize = 0;
    unsigned int Indices = 0;
    unsigned int VertexArrayPosOnlySize = 0;
    unsigned int VBOMemoryAllocationSize = 0;
    unsigned int EBOMemoryAllocationSize = 0;
};
