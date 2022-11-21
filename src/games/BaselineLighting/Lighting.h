#pragma once

#include "../../Utility.h"
#include "../../engine/GameUtils.h"
#include "../../engine/EngineBasicShapes.h"
#include "../../Camera.h"


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
    //glm::vec3 LightPosition = glm::vec3(30.8f, 30.8f, -100.0f);
    glm::vec3 LightPosition = glm::vec3(1.0f, 0.3f, -4.0f);

    CameraVariables cameraVariables;

    unsigned int EyePosUniformVecIndex = 3;

};

void GameInit(GameData* gameData)
{
    gameData->cameraVariables.cameraPosHome = glm::vec3(gameData->cameraVariables.cameraPosHome.x, 0.5f, -1.0f);
    gameData->cameraVariables.cameraPos = gameData->cameraVariables.cameraPosHome;

    glm::mat4 ModelMatrix_0(glm::mat4(1.0f));
    glm::mat4 ModelMatrix_1(glm::mat4(1.0f));
    for (unsigned int i = 0; i < gameData->NumberOfRenderSlots; ++i)
    {
        if (i == 0)
        {
            ModelMatrix_0 = glm::translate(ModelMatrix_0, gameData->LightPosition);
            ModelMatrix_0 = glm::scale(ModelMatrix_0, glm::vec3(0.1f, 0.1f, 0.1f));

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
            ModelMatrix_1 = glm::translate(ModelMatrix_1, glm::vec3(-0.0f, -0.2f, -3.0f));
            ModelMatrix_1 = glm::scale(ModelMatrix_1, glm::vec3(0.5f, 0.5f, 0.5f));

            gameData->RenderSlotArray[i].Model = gameData->models.Object.modelData;
            gameData->RenderSlotArray[i].NumAttributes = 3;
            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader_Object;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Object;
            gameData->RenderSlotArray[i].ViewMatrix = glm::mat4(1.0f);  
            gameData->RenderSlotArray[i].ProjectionMatrix = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.f);
            gameData->RenderSlotArray[i].ModelMatrix = ModelMatrix_1;
            gameData->RenderSlotArray[i].DepthTest = true;
            gameData->RenderSlotArray[i].uniforms.Vec3.push_back({ "LightColor", glm::vec3(1.0f, 1.0f, 1.0f) });
            gameData->RenderSlotArray[i].uniforms.Vec3.push_back({ "ObjectColor", glm::vec3(0.0f, 0.0f, 1.0f) });
            gameData->RenderSlotArray[i].uniforms.Float.push_back({ "AmbientLightStrength", 0.15f });
            gameData->RenderSlotArray[i].uniforms.Vec3.push_back({ "LightPosition", gameData->LightPosition });
            gameData->RenderSlotArray[1].uniforms.Vec3.push_back({ "EyePosition", gameData->cameraVariables.cameraPos });
        }
    }
}


void GameFrame(GLFWwindow* window, GameData* gameData, float DeltaTime, int* WindowWidth, int* WindowHeight)
{
    processInputCamera(window, &gameData->cameraVariables, DeltaTime);

    processWindowPos(window, WindowWidth, WindowHeight);
    gameData->RenderSlotArray[0].ProjectionMatrix = glm::perspective(glm::radians(45.f), float(*WindowWidth) / float(*WindowHeight), 0.1f, 100.f);
    gameData->RenderSlotArray[1].ProjectionMatrix = glm::perspective(glm::radians(45.f), float(*WindowWidth) / float(*WindowHeight), 0.1f, 100.f);

    auto viewMat = glm::mat4(1.f);
    viewMat = glm::lookAt(
            gameData->cameraVariables.cameraPos,
            gameData->cameraVariables.cameraPos + gameData->cameraVariables.cameraLookDirection,
            gameData->cameraVariables.cameraUp);

    gameData->RenderSlotArray[0].ViewMatrix = viewMat;
    gameData->RenderSlotArray[1].ViewMatrix = viewMat;

    gameData->RenderSlotArray[1].uniforms.Vec3[gameData->EyePosUniformVecIndex].second = gameData->cameraVariables.cameraPos;

    gameData->RenderSlotArray[0].Draw = true;
    gameData->RenderSlotArray[1].Draw = true;
}
