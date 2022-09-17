#pragma once

struct EngineBasicShapes
{
    struct Triangle
    {
        float VertexData[15] = 
        {
            -1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             1.0f, 0.0f,
             0.5f, 1.0f,
             0.0f, 0.0f
        };

        unsigned int VertexDataSize = 15;
        unsigned int Indices = 3;
        unsigned int TextureCoordOffset = 9 * sizeof(float);

        unsigned int NumPosPoints = 9;
    };

    struct Plane
    {
        float VertexData[20] = 
        {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             -1.0f, 1.0f, 0.0f,
             1.0f, 1.0f, 0.0f,
             0.0f, 0.0f,
             1.0f, 0.0f,
             0.0f, 1.0f,
             1.0f, 1.0f,
        };

        unsigned int IndexArray[6] = 
        {
            0, 1, 3,
            0, 2, 3
        };
        unsigned int VertexDataSize = 20 * sizeof(float);
        unsigned int IndexArraySize = 6 * sizeof(unsigned int);

        unsigned int Indices = 6;
        unsigned int TextureCoordOffset = 12 * sizeof(float);

        unsigned int VertexArrayPosOnlySize = 12 * sizeof(float);

    };
    
};
