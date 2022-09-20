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
        float VertexData[5*6*6] = 
        {
            /* The vertex annotations are given wrt to the face orientation.
             * For example the bottom face will have the notion of back and front vertices
             *
             * However, left and right faces do not follow this convention as they initially were annotated
             * with top/bottom notions (made sense visually I think).
             */

            /// Back Face

            // Tri 1
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom left
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom right

            // Tri 2
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top Left

            /// Front face

            // Tri 1
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom right
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top right

            // Tri 2
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top right
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left

            /// Left face

            // Tri 1
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top right
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top left
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom left

            // Tri 2
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom right
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top right

             /// Right face

            // Tri 1
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top left
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right

             // Tri 2
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom right
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top left
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left

            // Bottom face

             // Tri 1
             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Back left
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // Back right
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Front right

             // Tri 2
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Front right
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Front left
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Back left

            /// Top face

            // Tri 1
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Back left
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Front right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Back right

            // Tri 2
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Front right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Back left
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // Front left
        };

        unsigned int VertexDataSize = 5*6*6;

        unsigned int Indices = 5*6*6;

        unsigned int VertexArrayPosOnlySize = 5*6*6;

    };
    
};
