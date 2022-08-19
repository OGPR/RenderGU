#pragma once

#include "../../Utility.h"
#include "../../engine/GameUtils.h"

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

    }models;

    struct Textures
    {
        
        const char* TextureArray [2] =
        {
            "resources/container.jpg",
            "resources/wall.jpg",
        };

    }textures;


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

            // Tex coord passthrough VS
            const char* VertexShader_Tex = 
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;

            out vec2 TexCoord;

            uniform mat4 ModelMatrix;
            uniform mat4 ViewMatrix;
            uniform mat4 ProjectionMatrix;

            void main()
            {
                gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inPos, 1.0f);
                TexCoord = inTexCoord;

            }
            );

            const char* FragmentShader_Tex = 
            GLSL(330 core,
            out vec4 FragColor;
            in vec2 TexCoord;

            uniform sampler2D Texture;

            void main()
            {
                FragColor = texture(Texture, TexCoord);
            }
            );
            
            // Tex coord passthrough VS
            const char* VertexShader_Tex2 = 
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;

            out vec2 TexCoord;

            uniform mat4 ModelMatrix;
            uniform mat4 ViewMatrix;
            uniform mat4 ProjectionMatrix;

            void main()
            {
                gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inPos, 1.0f);
                TexCoord = inTexCoord;

            }
            );

            const char* FragmentShader_Tex2 = 
            GLSL(330 core,
            out vec4 FragColor;
            in vec2 TexCoord;

            uniform sampler2D Texture;

            void main()
            {
                FragColor = texture(Texture, TexCoord);
            }
            );

            

    }shaders;

    struct ShadersToModelAssignment
    {

        Slot slot1, slot2, slot3;

        unsigned int NumberOfSlots = 3;
        Slot SlotArray[3] = {slot1, slot2, slot3};


    }shadersToModelAssignment;


};

void GameInit(GameData* gameData)
{
    printf("Entering GameInit\n");
    for (int i = 0; i < gameData->shadersToModelAssignment.NumberOfSlots; ++i)
    {
        printf("Entering GameInit Number of slot loop\n");
        printf("NumberOf slots is %d\n", gameData->shadersToModelAssignment.NumberOfSlots);
        glm::mat4 ModelMatrix_0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));

        if (i == 0)
        {
            gameData->shadersToModelAssignment.SlotArray[i].models = &gameData->models;
            gameData->shadersToModelAssignment.SlotArray[i].shaders = &gameData->shaders;
            gameData->shadersToModelAssignment.SlotArray[i].Model = gameData->models.TriangleModel;
            gameData->shadersToModelAssignment.SlotArray[i].ModelIndices = gameData->models.TriangleModel_Indices;
            gameData->shadersToModelAssignment.SlotArray[i].VertexShader = gameData->shaders.VertexShader;
            gameData->shadersToModelAssignment.SlotArray[i].FragmentShader = gameData->shaders.FragmentShader;

            gameData->shadersToModelAssignment.SlotArray[i].ViewMatrix = glm::mat4(1.0f);  
            gameData->shadersToModelAssignment.SlotArray[i].ProjectionMatrix = glm::mat4(1.0f);
        }
        
        if(i == 0)
        {
            gameData->shadersToModelAssignment.SlotArray[i].ModelMatrix = glm::translate(
                    ModelMatrix_0,
                    glm::vec3(-1.0f, 0.0f, 0.0f));
        }


        if (i == 2)
        {
            gameData->shadersToModelAssignment.SlotArray[i].models = &gameData->models;
            gameData->shadersToModelAssignment.SlotArray[i].shaders = &gameData->shaders;
            gameData->shadersToModelAssignment.SlotArray[i].Model = gameData->models.TriangleModel;
            gameData->shadersToModelAssignment.SlotArray[i].ModelIndices = gameData->models.TriangleModel_Indices;
            gameData->shadersToModelAssignment.SlotArray[i].VertexShader = gameData->shaders.VertexShader_Tex;
            gameData->shadersToModelAssignment.SlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Tex;

            gameData->shadersToModelAssignment.SlotArray[i].TextureArrayIndex = 0;

            unsigned int TextureArrayIndex = gameData->shadersToModelAssignment.SlotArray[i].TextureArrayIndex;
            gameData->shadersToModelAssignment.SlotArray[i].Texture = gameData->textures.TextureArray[TextureArrayIndex]; 

            gameData->shadersToModelAssignment.SlotArray[i].ModelMatrix = glm::translate(
                    ModelMatrix_0,
                    glm::vec3(0.5f, 0.0f, 0.0f));
        }

        if (i == 1)
        {
            gameData->shadersToModelAssignment.SlotArray[i].models = &gameData->models;
            gameData->shadersToModelAssignment.SlotArray[i].shaders = &gameData->shaders;
            gameData->shadersToModelAssignment.SlotArray[i].Model = gameData->models.TriangleModel;
            gameData->shadersToModelAssignment.SlotArray[i].ModelIndices = gameData->models.TriangleModel_Indices;
            gameData->shadersToModelAssignment.SlotArray[i].VertexShader = gameData->shaders.VertexShader_Tex2;
            gameData->shadersToModelAssignment.SlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Tex2;

            gameData->shadersToModelAssignment.SlotArray[i].TextureArrayIndex = 1;

            unsigned int TextureArrayIndex = gameData->shadersToModelAssignment.SlotArray[i].TextureArrayIndex;
            gameData->shadersToModelAssignment.SlotArray[i].Texture = gameData->textures.TextureArray[TextureArrayIndex]; 

            gameData->shadersToModelAssignment.SlotArray[i].ModelMatrix = glm::translate(
                    ModelMatrix_0,
                    glm::vec3(1.0f, 0.0f, 0.0f));
        }

    }
    printf("Exiting GameInit\n");

}


void GameFrame(GLFWwindow* window, GameData* gameData)
{
    gameData->shadersToModelAssignment.SlotArray[0].Draw = true;
    gameData->shadersToModelAssignment.SlotArray[1].Draw = true;
    gameData->shadersToModelAssignment.SlotArray[2].Draw = true;

}



