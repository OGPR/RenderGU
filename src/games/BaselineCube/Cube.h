#pragma once

#include "../../Utility.h"
#include "../../engine/GameUtils.h"
#include "../../engine/EngineBasicShapes.h"


struct GameData
{
    
    struct Models
    {
        EngineBasicShapes::Cube Cube;

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


    RenderSlot renderSlot1, renderSlot2, renderSlot3;

    unsigned int NumberOfRenderSlots = 3;
    RenderSlot RenderSlotArray[3] = {renderSlot1, renderSlot2, renderSlot3};

    // Initial values
    float RotDeg_1 = 0.0f;
    float RotDeg_2 = 0.0f;
    float RotDeg_3 = 0.0f;

};

void GameInit(GameData* gameData)
{
    for (unsigned int i = 0; i < gameData->NumberOfRenderSlots; ++i)
    {

        if (i == 0)
        {
            glm::mat4 ViewMatrix_0 = glm::mat4(1.0f);  
            glm::mat4 ProjectionMatrix_0 = glm::perspective(glm::radians(45.f), 800.f/600.f, 0.1f, 100.f);

            glm::mat4 ModelMatrix_0 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, -5.0f));
            ModelMatrix_0 = glm::rotate(ModelMatrix_0, glm::radians(gameData->RotDeg_1), glm::vec3(0.0f, 1.0f, 0.0f));
            ModelMatrix_0 = glm::scale(ModelMatrix_0, glm::vec3(0.8f, 0.8f, 0.8f));

            gameData->RenderSlotArray[i].ModelMatrix = ModelMatrix_0; 

            gameData->RenderSlotArray[i] = 
            {
                gameData->models.Cube.modelData,
                1,
                gameData->shaders.VertexShader,
                gameData->shaders.FragmentShader,
                nullptr,
                0,
                ModelMatrix_0,
                ViewMatrix_0,
                ProjectionMatrix_0,
                false,
                true
            };
        }
        
        if (i == 2)
        {

            gameData->RenderSlotArray[i].Model = gameData->models.Cube.modelData;

            gameData->RenderSlotArray[i].NumAttributes = 2;

            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader_Tex;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Tex;

            gameData->RenderSlotArray[i].TextureArrayIndex = 0;

            unsigned int TextureArrayIndex = gameData->RenderSlotArray[i].TextureArrayIndex;
            gameData->RenderSlotArray[i].Texture = gameData->textures.TextureArray[TextureArrayIndex]; 

            glm::mat4 ModelMatrix_0 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
            ModelMatrix_0 = glm::rotate(ModelMatrix_0, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            ModelMatrix_0 = glm::scale(ModelMatrix_0, glm::vec3(0.8f, 0.8f, 0.8f));

            gameData->RenderSlotArray[i].ModelMatrix = ModelMatrix_0; 

            gameData->RenderSlotArray[i].ProjectionMatrix = glm::perspective(glm::radians(45.f), 800.f/600.f, 0.1f, 100.f);

        }

        if (i == 1)
        {

            gameData->RenderSlotArray[i].Model = gameData->models.Cube.modelData;

            gameData->RenderSlotArray[i].NumAttributes = 2;


            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader_Tex2;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Tex2;

            gameData->RenderSlotArray[i].TextureArrayIndex = 1;

            unsigned int TextureArrayIndex = gameData->RenderSlotArray[i].TextureArrayIndex;
            gameData->RenderSlotArray[i].Texture = gameData->textures.TextureArray[TextureArrayIndex]; 

            glm::mat4 ModelMatrix_0 = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, -5.0f));
            ModelMatrix_0 = glm::rotate(ModelMatrix_0, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            ModelMatrix_0 = glm::scale(ModelMatrix_0, glm::vec3(0.8f, 0.8f, 0.8f));

            gameData->RenderSlotArray[i].ModelMatrix = ModelMatrix_0; 

            gameData->RenderSlotArray[i].ProjectionMatrix = glm::perspective(glm::radians(45.f), 800.f/600.f, 0.1f, 100.f);
        }

    }
}


void GameFrame(GLFWwindow* window, GameData* gameData, float DeltaTime)
{
    glm::mat4 ModelMatrix_0 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.0f, -5.0f));
    ModelMatrix_0 = glm::rotate(ModelMatrix_0, glm::radians(gameData->RotDeg_1 += 10 * DeltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix_0 = glm::scale(ModelMatrix_0, glm::vec3(0.8f, 0.8f, 0.8f));
    gameData->RenderSlotArray[0].ModelMatrix = ModelMatrix_0; 

    ModelMatrix_0 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    ModelMatrix_0 = glm::rotate(ModelMatrix_0, glm::radians(gameData->RotDeg_2 -= 10 * DeltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix_0 = glm::scale(ModelMatrix_0, glm::vec3(0.8f, 0.8f, 0.8f));
    gameData->RenderSlotArray[2].ModelMatrix = ModelMatrix_0; 

    ModelMatrix_0 = glm::translate(glm::mat4(1.0f), glm::vec3(1.5f, 0.0f, -5.0f));
    ModelMatrix_0 = glm::rotate(ModelMatrix_0, glm::radians(gameData->RotDeg_3 += 12 * DeltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
    ModelMatrix_0 = glm::scale(ModelMatrix_0, glm::vec3(0.8f, 0.8f, 0.8f));
    gameData->RenderSlotArray[1].ModelMatrix = ModelMatrix_0; 

    gameData->RenderSlotArray[0].Draw = true;
    gameData->RenderSlotArray[1].Draw = true;
    gameData->RenderSlotArray[2].Draw = true;

}