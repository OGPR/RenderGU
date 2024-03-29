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
        EngineBasicShapes::Plane Plane;
    }models;

    struct Shaders
    {
        const char* VertexShader = "../../../SPIRV_Bin/InstancingTest.vert.spv";
        const char* FragmentShader = "../../../SPIRV_Bin/InstancingTest.frag.spv";

        const char* VertexShaderPlane = "../../../SPIRV_Bin/Plane.vert.spv";
    }shaders;

    struct GlobalGameVariables
    {
        bool HasInstancing = true;
        unsigned int InstancingModelMatrixShaderInputLocation = 3;
    }globalGameVariables;

    unsigned int NumberOfRenderSlots = 3;
    RenderSlot RenderSlotArray[3] = {};

    glm::vec3 Translation_Slot1 = glm::vec3(0.1f, 0.0f, 0.0f);
    glm::vec3 Translation_Slot2 = glm::vec3(0.105f, 0.0f, 0.0f);
};

void GameInit(GameData* gameData)
{
    // First slot
    gameData->RenderSlotArray[0]._2D = true;

    std::vector<glm::mat4> ModelMatrixVec;
    for (unsigned int multiplier = 1; multiplier < 20; multiplier += 2)
    {
        // Remember, scale(translate) is T*S
        ModelMatrixVec.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-0.1f * multiplier, 0.0f, 0.0f)), glm::vec3(0.1f, 0.1f, 0.1f)));
        ModelMatrixVec.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.1f * multiplier, 0.0f, 0.0f)), glm::vec3(0.1f, 0.1f, 0.1f)));
    }

    gameData->RenderSlotArray[0].Model = gameData->models.Triangle.modelData;
    gameData->RenderSlotArray[0].NumAttributes = 1;
    gameData->RenderSlotArray[0].VertexShader = gameData->shaders.VertexShader;
    gameData->RenderSlotArray[0].FragmentShader = gameData->shaders.FragmentShader;
    gameData->RenderSlotArray[0].ViewMatrix = glm::mat4(1.0f);
    gameData->RenderSlotArray[0].uniforms.Vec3.push_back({ "Color", glm::vec3(0.97f, 0.51f, 0.47f) });
    gameData->RenderSlotArray[0].ModelMatrixCollection = ModelMatrixVec;

    // Second Slot
    gameData->RenderSlotArray[1]._2D = true;

    std::vector<glm::mat4> ModelMatrixVec_Slot2;
    for (unsigned int multiplier = 1; multiplier < 20; multiplier += 2)
    {
        // Remember, scale(translate) is T*S
        ModelMatrixVec_Slot2.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-0.1f * multiplier, 0.0f, 0.0f)), glm::vec3(0.1f, 0.1f, 0.1f)));
        ModelMatrixVec_Slot2.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.1f * multiplier, 0.0f, 0.0f)), glm::vec3(0.1f, 0.1f, 0.1f)));
    }

    gameData->RenderSlotArray[1].Model = gameData->models.Plane.modelData;
    gameData->RenderSlotArray[1].NumAttributes = 1;
    gameData->RenderSlotArray[1].VertexShader = gameData->shaders.VertexShader;
    gameData->RenderSlotArray[1].FragmentShader = gameData->shaders.FragmentShader;
    gameData->RenderSlotArray[1].ViewMatrix = glm::mat4(1.0f);
    gameData->RenderSlotArray[1].uniforms.Vec3.push_back({ "Color", glm::vec3(0.97f, 0.51f, 0.47f) });
    gameData->RenderSlotArray[1].ModelMatrixCollection = ModelMatrixVec_Slot2;

    // Third Slot
    gameData->RenderSlotArray[2]._2D = true;

    glm::mat4 ModelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));

    gameData->RenderSlotArray[2].Model = gameData->models.Plane.modelData;
    gameData->RenderSlotArray[2].NumAttributes = 1;
    gameData->RenderSlotArray[2].VertexShader = gameData->shaders.VertexShaderPlane;
    gameData->RenderSlotArray[2].FragmentShader = gameData->shaders.FragmentShader;
    gameData->RenderSlotArray[2].ViewMatrix = glm::mat4(1.0f);
    gameData->RenderSlotArray[2].uniforms.Vec3.push_back({ "Color", glm::vec3(0.54f, 0.17f, 0.89f) });
    gameData->RenderSlotArray[2].ModelMatrix = ModelMatrix;
}

void GameFrame(GLFWwindow* window, GameData* gameData, float DeltaTime)
{
    // First Slot
    gameData->RenderSlotArray[0].Draw = true;

    std::vector<glm::mat4> ModelMatrixVec;
    for (unsigned int n = 1; n < gameData->RenderSlotArray[0].ModelMatrixCollection.size() ; n += 2)
    {
        float TransX = gameData->Translation_Slot1.x * n;
        float TransY = gameData->Translation_Slot1.y + (0.01 * DeltaTime);
        gameData->Translation_Slot1.y = TransY;

        // Remember, scale(translate) is T*S
        ModelMatrixVec.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(TransX, TransY, gameData->Translation_Slot1.z)), glm::vec3(0.1f, 0.1f, 0.1f)));
        ModelMatrixVec.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-TransX, TransY, gameData->Translation_Slot1.z)), glm::vec3(0.1f, 0.1f, 0.1f)));
    }
    gameData->RenderSlotArray[0].ModelMatrixCollection = ModelMatrixVec;

    // Second Slot
    gameData->RenderSlotArray[1].Draw = true;

    std::vector<glm::mat4> ModelMatrixVec_Slot2;
    for (unsigned int n = 1; n < gameData->RenderSlotArray[0].ModelMatrixCollection.size() ; n += 2)
    {
        float TransX = gameData->Translation_Slot2.x * n;
        float TransY = gameData->Translation_Slot2.y - (0.01 * DeltaTime);
        gameData->Translation_Slot2.y = TransY;

        // Remember, scale(translate) is T*S
        ModelMatrixVec_Slot2.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(TransX, TransY, gameData->Translation_Slot2.z)), glm::vec3(0.1f, 0.1f, 0.1f)));
        ModelMatrixVec_Slot2.push_back(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(-TransX, TransY, gameData->Translation_Slot2.z)), glm::vec3(0.1f, 0.1f, 0.1f)));
    }
    gameData->RenderSlotArray[1].ModelMatrixCollection = ModelMatrixVec_Slot2;

    // Third Slot
    gameData->RenderSlotArray[2].Draw = true;
}
