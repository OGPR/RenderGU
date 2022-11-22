#pragma once
#include "../../Utility.h"
#include "../../engine/GameUtils.h"
#include "../../engine/EngineBasicShapes.h"


struct GameData
{
    struct WindowSpecification
    {
        int WindowWidth = 800;
        int WindowHeight = 600;
        const char* WindowTitle = "Transformation Test 2D";
        int WindowXPos = 800;
        int WindowYPos = 280;
    } windowSpecification;

    struct Models
    {
        EngineBasicShapes::Triangle Triangle;
    }models;

    struct Shaders
    {
        const char* VertexShader = "../../../SPIRV_Bin/2DTransformationTest.vert.spv";
        const char* FragmentShader = "../../../SPIRV_Bin/2DTransformationTest.frag.spv";
    }shaders;


    RenderSlot renderSlot1;

    unsigned int NumberOfRenderSlots = 1;
    RenderSlot RenderSlotArray[1] = {renderSlot1};

};

void GameInit(GameData* gameData)
{
    gameData->RenderSlotArray->_2D = true;
    glm::mat4 ModelMatrix_0 = glm::mat4(1.0f);

    gameData->RenderSlotArray->Model = gameData->models.Triangle.modelData;
    gameData->RenderSlotArray->NumAttributes = 1;
    gameData->RenderSlotArray->VertexShader = gameData->shaders.VertexShader;
    gameData->RenderSlotArray->FragmentShader = gameData->shaders.FragmentShader;
    gameData->RenderSlotArray->ViewMatrix = glm::mat4(1.0f);
    gameData->RenderSlotArray->uniforms.Vec3.push_back({ "Color", glm::vec3(0.97f, 0.51f, 0.47f) });

    gameData->RenderSlotArray->ModelMatrix = ModelMatrix_0;
}



void GameFrame(GLFWwindow* window, GameData* gameData, float DeltaTime)
{
    gameData->RenderSlotArray->Draw = true;
}
