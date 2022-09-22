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

    struct Cube
    {
        float VertexData[5*4*6] = 
        {
            /* The vertex annotations are given wrt to the face orientation.
             * For example the bottom face will have the notion of back and front vertices
             *
             * However, left and right faces do not follow this convention as they initially were annotated
             * with top/bottom notions (made sense visually I think).
             */

            /// Back Face

            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom left
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top Left

            /// Front face

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom right
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top right
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top left

            /// Left face

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top right
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top left
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom right

             /// Right face

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top left
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom right
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left

            // Bottom face

             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Back left
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // Back right
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Front right
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Front left

            /// Top face

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Back left
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Back right
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Front right
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // Front left
        };

        unsigned int IndexArray[6*6] = 
        {
            // Back Face
            0, 1, 2,
            0, 3, 2,

            // Front Face
            4, 5, 6,
            4, 7, 6,

            // Left face
            8, 9, 10,
            8, 11, 10,

            // Right face
            12, 13, 14,
            12, 15, 14,

            // Bottom face
            16, 17, 18,
            16, 19, 18,

            // Top face
            20, 21, 22,
            20, 23, 22
        };

        unsigned int IndexArraySize = 6 * 6 * sizeof(unsigned int);

        unsigned int VertexDataSize = 5*6*6;

        unsigned int Indices = 5*6*6;

        unsigned int VertexArrayPosOnlySize = 5*6*6;

    };
    
};
