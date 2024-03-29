#pragma once
#include "EngineModelDataInterface.h" 

struct EngineBasicShapes
{
    struct Triangle
    {
        Triangle()
        {
            modelData.VertexData = VertexData;
            modelData.Indices = Indices;
            modelData.VBOMemoryAllocationSize = VBOMemoryAllocationSize;
            modelData.Name = "EngineBasicShapes::Triangle";
            modelData.AttributeArray = AttributeArray;
        }

        ModelData modelData;

        Attribute AttributeArray[2] =
        {
            {
                3,
                0,
                0
            },

            {
                2,
                0,
                (void*)(9 * sizeof(float)) 
            }
        };

        float VertexData[15] = 
        {
            -1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             1.0f, 0.0f,
             0.5f, 1.0f,
             0.0f, 0.0f
        };

        unsigned int Indices = 3;
        unsigned int VBOMemoryAllocationSize = 15 * sizeof(float);
    };

    struct Plane
    {
        Plane()
        {
            modelData.VertexData = VertexData;
            modelData.IndexArray = IndexArray; 
            modelData.Indices = Indices;
            modelData.VBOMemoryAllocationSize = VBOMemoryAllocationSize;
            modelData.EBOMemoryAllocationSize = EBOMemoryAllocationSize;
            modelData.Name = "EngineBasicShapes::Plane";
            modelData.AttributeArray = AttributeArray;

        }

        ModelData modelData;

        Attribute AttributeArray[2] =
        {
            {
                3,
                0,
                0
            },

            {
                2,
                0,
                (void*)(12 * sizeof(float)) 
            }
        };

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

        unsigned int Indices = 6;
        unsigned int VBOMemoryAllocationSize = 20 * sizeof(float);
        unsigned int EBOMemoryAllocationSize = 6 * sizeof(unsigned int) ;
    };

    struct Cube
    {
        Cube()
        {
            modelData.VertexData = VertexData;
            modelData.IndexArray = IndexArray; 
            modelData.Indices = Indices;
            modelData.VBOMemoryAllocationSize = VBOMemoryAllocationSize;
            modelData.EBOMemoryAllocationSize = EBOMemoryAllocationSize;
            modelData.Name = "EngineBasicShapes::Cube";
            modelData.AttributeArray = AttributeArray;
        }

        ModelData modelData;

        Attribute AttributeArray[3] =
        {
            // Pos
            {
                3,
                8*sizeof(float),
                0
            },

            // Tex
            {
                2,
                8*sizeof(float),
                (void*)(3 * sizeof(float)) 
            },

            // Normal
            {
                3,
                8*sizeof(float),
                (void*)(5 * sizeof(float)) 
            }

        };

        float VertexData[8*4*6] = 
        {
            /* The vertex annotations are given wrt to the face orientation.
             * For example the bottom face will have the notion of back and front vertices
             *
             * However, left and right faces do not follow this convention as they initially were annotated
             * with top/bottom notions (made sense visually I think).
             */

            /// Back Face

            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // Bottom left
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,// Bottom right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,// Top right
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,// Top Left

            /// Front face

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,// Bottom left
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,// Bottom right
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,// Top right
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// Top left

            /// Left face

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,// Top right
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,// Top left
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,// Bottom left
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,// Bottom right

             /// Right face

             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// Top left
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// Top right
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,// Bottom right
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// Bottom left

            // Bottom face

             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,// Back left
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,// Back right
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,// Front right
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,// Front left

            /// Top face

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// Back left
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,// Back right
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,// Front right
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,// Front left
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

        unsigned int Indices = 5*6*6;
        unsigned int VBOMemoryAllocationSize = 8 * 4 *6 * sizeof(float);
        unsigned int EBOMemoryAllocationSize = 6 * 6 * sizeof(unsigned int) ;
    };
};
