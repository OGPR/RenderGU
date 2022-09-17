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
    
};
