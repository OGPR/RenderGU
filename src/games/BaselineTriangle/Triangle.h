#pragma once

#include "../../Utility.h"
#include "../../engine/GameUtils.h"
#include "../../engine/EngineBasicShapes.h"


struct GameData
{
    
    struct Models
    {
        EngineBasicShapes::Triangle Triangle;

    }models;

    struct Textures
    {
        
        const char* TextureArray [2] =
        {
            "../../../resources/container.jpg",
            "../../../resources/wall.jpg",
        };

    }textures;


    struct Shaders
    {
        const char* VertexShader = "../../../SPIRV_Bin/VertexShader.vert.spv"; 

        const char* FragmentShader = "../../../SPIRV_Bin/FragmentShader.frag.spv";

        // Tex coord passthrough VS
        const char* VertexShader_Tex = "../../../SPIRV_Bin/VertexShader_Tex.vert.spv";

        const char* FragmentShader_Tex = "../../../SPIRV_Bin/FragmentShader_Tex.frag.spv"; 
        
        // Tex coord passthrough VS
        const char* VertexShader_Tex2 = "../../../SPIRV_Bin/VertexShader_Tex2.vert.spv"; 

        const char* FragmentShader_Tex2 = "../../../SPIRV_Bin/FragmentShader_Tex2.frag.spv";

    }shaders;


    RenderSlot renderSlot1, renderSlot2, renderSlot3;

    unsigned int NumberOfRenderSlots = 3;
    RenderSlot RenderSlotArray[3] = {renderSlot1, renderSlot2, renderSlot3};

};

void GameInit(GameData* gameData)
{
    for (unsigned int i = 0; i < gameData->NumberOfRenderSlots; ++i)
    {
        gameData->RenderSlotArray[i]._2D = true;
        glm::mat4 ModelMatrix_0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));

        if (i == 0)
        {
            gameData->RenderSlotArray[i].Model = gameData->models.Triangle.modelData;

            gameData->RenderSlotArray[i].NumAttributes = 1;

            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader;

            gameData->RenderSlotArray[i].ViewMatrix = glm::mat4(1.0f);
        }

        if(i == 0)
        {
            gameData->RenderSlotArray[i].ModelMatrix = glm::translate(
                    ModelMatrix_0,
                    glm::vec3(-1.0f, 0.0f, 0.0f));
        }


        if (i == 2)
        {
            gameData->RenderSlotArray[i].Model = gameData->models.Triangle.modelData;

            gameData->RenderSlotArray[i].NumAttributes = 2;

            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader_Tex;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Tex;

            gameData->RenderSlotArray[i].TextureArrayIndex = 0;

            unsigned int TextureArrayIndex = gameData->RenderSlotArray[i].TextureArrayIndex;
            gameData->RenderSlotArray[i].Texture = gameData->textures.TextureArray[TextureArrayIndex];

            gameData->RenderSlotArray[i].ModelMatrix = glm::translate(
                    ModelMatrix_0,
                    glm::vec3(0.5f, 0.0f, 0.0f));
        }

        if (i == 1)
        {
            gameData->RenderSlotArray[i].Model = gameData->models.Triangle.modelData;

            gameData->RenderSlotArray[i].NumAttributes = 2;
            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader_Tex2;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Tex2;

            gameData->RenderSlotArray[i].TextureArrayIndex = 1;

            unsigned int TextureArrayIndex = gameData->RenderSlotArray[i].TextureArrayIndex;
            gameData->RenderSlotArray[i].Texture = gameData->textures.TextureArray[TextureArrayIndex];

            gameData->RenderSlotArray[i].ModelMatrix = glm::translate(
                    ModelMatrix_0,
                    glm::vec3(1.0f, 0.0f, 0.0f));
        }

    }

}



void GameFrame(GLFWwindow* window, GameData* gameData, float DeltaTime)
{
    gameData->RenderSlotArray[0].Draw = true;
    gameData->RenderSlotArray[1].Draw = true;
    gameData->RenderSlotArray[2].Draw = true;

}
