#pragma once

#include "../../Utility.h"
#include "../../engine/GameUtils.h"
#include "../../engine/EngineBasicShapes.h"


struct GameData
{
    
    struct Models
    {
        EngineBasicShapes::Cube LightSource;
        EngineBasicShapes::Cube Object;

    }models;

    struct Shaders
    {
        const char* VertexShader = "../../../SPIRV_Bin/LightSource.vert.spv"; 
        const char* FragmentShader = "../../../SPIRV_Bin/LightSource.frag.spv";

        const char* VertexShader_Object = "../../../SPIRV_Bin/Object.vert.spv"; 
        const char* FragmentShader_Object = "../../../SPIRV_Bin/Object.frag.spv";

    }shaders;

    RenderSlot renderSlot1, renderSlot2;
    unsigned int NumberOfRenderSlots = 2;
    RenderSlot RenderSlotArray[2] = { renderSlot1, renderSlot2 };
};

void GameInit(GameData* gameData)
{
    glm::mat4 ModelMatrix_0(glm::mat4(1.0f));
    glm::mat4 ModelMatrix_1(glm::mat4(1.0f));
    for (unsigned int i = 0; i < gameData->NumberOfRenderSlots; ++i)
    {
        if (i == 0)
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
            gameData->RenderSlotArray[i].uniforms.Vec3.push_back({ "LightColor", glm::vec3(1.0f, 1.0f, 1.0f) });
        }

        if (i == 1)
        {
			ModelMatrix_1 = glm::translate(ModelMatrix_1, glm::vec3(-0.0f, -0.2f, -2.0f));
			ModelMatrix_1 = glm::scale(ModelMatrix_1, glm::vec3(0.5f, 0.5f, 0.5f));

			gameData->RenderSlotArray[i].Model = gameData->models.Object.modelData;
			gameData->RenderSlotArray[i].NumAttributes = 1;
			gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader_Object;
			gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Object;
			gameData->RenderSlotArray[i].ViewMatrix = glm::mat4(1.0f);  
			gameData->RenderSlotArray[i].ProjectionMatrix = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f);
			gameData->RenderSlotArray[i].ModelMatrix = ModelMatrix_1;
			gameData->RenderSlotArray[i].DepthTest = true;
            gameData->RenderSlotArray[i].uniforms.Vec3.push_back({ "LightColor", glm::vec3(1.0f, 1.0f, 1.0f) });
            gameData->RenderSlotArray[i].uniforms.Vec3.push_back({ "ObjectColor", glm::vec3(0.0f, 0.0f, 1.0f) });
        }
    }
}


void GameFrame(GLFWwindow* window, GameData* gameData, float DeltaTime)
{
    gameData->RenderSlotArray[0].Draw = true;
    gameData->RenderSlotArray[1].Draw = true;
}
