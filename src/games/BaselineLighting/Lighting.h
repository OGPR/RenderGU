#pragma once

#include "../../Utility.h"
#include "../../engine/GameUtils.h"
#include "../../engine/EngineBasicShapes.h"


struct GameData
{
    
    struct Models
    {
        EngineBasicShapes::Cube LightSource;

    }models;

    struct Shaders
    {
        const char* VertexShader = "../../../SPIRV_Bin/LightSource.vert.spv"; 
        const char* FragmentShader = "../../../SPIRV_Bin/LightSource.frag.spv";

    }shaders;

    RenderSlot renderSlot1;
    unsigned int NumberOfRenderSlots = 1;
    RenderSlot RenderSlotArray[1] = { renderSlot1 };
};

void GameInit(GameData* gameData)
{
    glm::mat4 ModelMatrix_0(glm::mat4(1.0f));
    for (unsigned int i = 0; i < gameData->NumberOfRenderSlots; ++i)
    {
        ModelMatrix_0 = glm::translate(ModelMatrix_0, glm::vec3(30.8f, 30.8f, -100.0f));
        ModelMatrix_0 = glm::scale(ModelMatrix_0, glm::vec3(0.5f, 0.5f, 0.5f));

		gameData->RenderSlotArray[i].Model = gameData->models.LightSource.modelData;
		gameData->RenderSlotArray[i].NumAttributes = 1;
		gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader;
		gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader;
		gameData->RenderSlotArray[i].ViewMatrix = glm::mat4(1.0f);  
		gameData->RenderSlotArray[i].ProjectionMatrix = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f);
        gameData->RenderSlotArray[i].ModelMatrix = ModelMatrix_0;
        gameData->RenderSlotArray[i].DepthTest = true;
    }
}


void GameFrame(GLFWwindow* window, GameData* gameData, float DeltaTime)
{
    gameData->RenderSlotArray[0].Draw = true;
}
