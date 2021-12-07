#pragma once
#include "../../VertexSpecification_Common.h"
#include <cstdio>
#include "data.h"

unsigned int vertex_specification_floor(float* vertex, unsigned int numberOfEntries)
{
    if (_floorData.numberOfEntries != numberOfEntries)
    {
        printf("Rendering the floor:\n");
        printf("Expected number of entries to be %d, but have received %d", _floorData.numberOfEntries, numberOfEntries);
        printf("\n Rendering has continued, but if is not what you expect, this might be one of the reasons why.");
    }

    BindVBO(CreateVBO());
    AllocateMemoryVBO(numberOfEntries, vertex);
    unsigned int VAO = CreateVAO(); // Will be returned, and set prior to return, so need to store it here
    BindVAO(VAO);

    FloorAttributes FA;
    SetAttribute(FA.pos.index, FA.pos.size, FA.pos.stride, FA.pos.offset);
    SetAttribute(FA.tex.index, FA.tex.size, FA.tex.stride, FA.tex.offset);

    return VAO;
}
