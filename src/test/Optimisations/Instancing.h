#pragma once
#include "../../Utility.h"
#include "../../engine/GameUtils.h"
#include "../../engine/EngineBasicShapes.h"
#include <vector>


struct GameData
{
    struct WindowSpecification
    {
        int WindowWidth = 800;
        int WindowHeight = 600;
        const char* WindowTitle = "Instancing Test";
        int WindowXPos = 800;
        int WindowYPos = 280;
    } windowSpecification;

    struct Models
    {
        EngineBasicShapes::Triangle Triangle;
    }models;

    struct Shaders
    {
        const char* VertexShader = "../../../SPIRV_Bin/InstancingTest.vert.spv";
        const char* FragmentShader = "../../../SPIRV_Bin/InstancingTest.frag.spv";
    }shaders;

    unsigned int NumberOfRenderSlots = 1;
    RenderSlot RenderSlotArray[1] = {};
};

glm::mat4 RGU_Translate(glm::mat4 Matrix, float X ,float Y ,float Z = 0)
{
    return glm::translate(Matrix, glm::vec3(X, Y, Z));
}

glm::mat4 RGU_Scale(glm::mat4 Matrix, float X ,float Y ,float Z = 0)
{
    return glm::scale(Matrix, glm::vec3(X, Y, Z));
}

glm::mat4 RGU_Rotate(glm::mat4 Matrix, float RotDeg, float X ,float Y ,float Z = 0)
{
    return glm::rotate(Matrix, glm::radians(RotDeg), glm::vec3(X, Y, Z));
}

void GameInit(GameData* gameData)
{
    gameData->RenderSlotArray[0]._2D = true;

    std::vector<glm::mat4> ModelMatrixVec
    {
        // Remember, scale(translate) is T*S
        glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f)), glm::vec3(0.1f, 0.1f, 0.1f)),
        glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f)), glm::vec3(0.1f, 0.1f, 0.1f))
    };

    gameData->RenderSlotArray[0].Model = gameData->models.Triangle.modelData;
    gameData->RenderSlotArray[0].NumAttributes = 1;
    gameData->RenderSlotArray[0].VertexShader = gameData->shaders.VertexShader;
    gameData->RenderSlotArray[0].FragmentShader = gameData->shaders.FragmentShader;
    gameData->RenderSlotArray[0].ViewMatrix = glm::mat4(1.0f);
    gameData->RenderSlotArray[0].uniforms.Vec3.push_back({ "Color", glm::vec3(0.97f, 0.51f, 0.47f) });



    //gameData->RenderSlotArray[0].ModelMatrix = ModelMatrixVec[0];
    gameData->RenderSlotArray[0].ModelMatrixCollection = ModelMatrixVec;

}

void GameFrame(GLFWwindow* window, GameData* gameData, float DeltaTime)
{
    gameData->RenderSlotArray[0].Draw = true;
}
