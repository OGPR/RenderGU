#pragma once

#include "../../Utility.h"

// This is our triangle "game"

// What does our engine need?
// A function that represents each frame, with arguments GLFwindow* and a GameData*
//
// From a game point of view, we would like to descirbe what we want:
//
// In this case, we want to draw a triangle each frame. 
//
// We are expected to write shaders - VS and FS at a minumum
//
// We want to either use a predefined model, or make our own.
//



    

struct GameData
{
    struct Models
    {
        // RenderGU will require non-interleaved vertex data:
        // For the moment 3D position, and 2D texture coords,
        // BUT for the NOW moment, just do position to get things working
        // without textures
        
        // For now manually create the model array here
        // Use NDC
        float TriangleModel[15] = 
        {
            -1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             1.0f, 0.0f,
             0.0f, 1.0f,
             0.0f, 0.0f
        };
        
        unsigned int TriangleModel_Indices = 3;

    };

    struct Shaders
    {
            const char* VertexShader = 
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;

            uniform mat4 ModelMatrix;
            uniform mat4 ViewMatrix;
            uniform mat4 ProjectionMatrix;

            void main()
            {
                gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inPos, 1.0f);
            }
            );

            const char* FragmentShader = 
            GLSL(330 core,
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(0.1f, 0.2f, 0.3f, 1.0f);
            }
            );

    };

    struct ShadersToModelAssignment
    {
        struct Slot1
        {
            Models models;
            Shaders shaders;
            float* Model = models.TriangleModel;
            const unsigned int ModelIndices = models.TriangleModel_Indices; 
            const char* VertexShader = shaders.VertexShader;
            const char* FragmentShader = shaders.FragmentShader;

            glm::mat4 ModelMatrix = glm::mat4(1.0f);
            glm::mat4 ViewMatrix = glm::mat4(1.0f);
            glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

            bool Draw = false;

        }slot1;


    }shadersToModelAssignment;


};

void GameFrame(GLFWwindow* window, GameData* gameData)
{
    gameData->shadersToModelAssignment.slot1.Draw = true;
}



