#pragma once

#include "model.h"
#include <glad/glad.h>

struct FloorData
{
    int numberOfEntries = 3*6 + 2*6;
    float* data = floor_model;
} _floorData;

struct FloorAttributes
{
    struct Position
    {
        unsigned int index = 0;
        unsigned int size = 3;
        GLsizei stride = 5 * sizeof(float);
        const void* offset = 0;
    }pos;

    struct Texture
    {
        unsigned int index = 1;
        unsigned int size = 2;
        GLsizei stride = 5 * sizeof(float) ;
        const void* offset = (void * )(3 * sizeof(float));
    }tex;

};
