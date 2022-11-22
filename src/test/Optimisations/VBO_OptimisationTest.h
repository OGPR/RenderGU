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
        const char* WindowTitle = "VBO Optimisation Test";
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
        // Using 2D Transformation test shaders
        const char* VertexShader = "../../../SPIRV_Bin/2DTransformationTest.vert.spv";
        const char* FragmentShader = "../../../SPIRV_Bin/2DTransformationTest.frag.spv";
    }shaders;

    unsigned int NumberOfRenderSlots = 22;
    RenderSlot RenderSlotArray[22] =
    {
    };

    std::vector<float> XTrans
    {
        -0.9f,
        -0.7f,
        -0.5f,
        -0.3f,
        -0.1f,
         0.1f,
         0.3f,
         0.5f,
         0.7f,
         0.9f
    };

    std::vector<float> YTrans
            {
                    -0.9f,
                    -0.7f,
                    -0.5f,
                    -0.3f,
                    -0.1f,
                    0.1f,
                    0.3f,
                    0.5f,
                    0.7f,
                    0.9f,
                    -0.7f,
                    -0.5f,
                    -0.3f,
                    -0.1f,
                    0.1f,
                    0.3f,
                    0.5f,
                    0.7f,
                    0.9f,
                    -0.0f
            };
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
    for (unsigned int i = 0; i < gameData->NumberOfRenderSlots; ++i)
    {
        if (i < gameData->NumberOfRenderSlots - 2)
        {
            gameData->RenderSlotArray[i]._2D = true;
            glm::mat4 ModelMatrix_0 = glm::mat4(1.0f);

            gameData->RenderSlotArray[i].Model = gameData->models.Triangle.modelData;
            gameData->RenderSlotArray[i].NumAttributes = 1;
            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader;
            gameData->RenderSlotArray[i].ViewMatrix = glm::mat4(1.0f);
            gameData->RenderSlotArray[i].uniforms.Vec3.push_back({ "Color", glm::vec3(0.97f, 0.51f, 0.47f) });

            ModelMatrix_0 = RGU_Translate(ModelMatrix_0, gameData->XTrans[i % 10], gameData->YTrans[i]);
            ModelMatrix_0 = RGU_Scale(ModelMatrix_0, 0.1f, 0.1f);

            gameData->RenderSlotArray[i].ModelMatrix = ModelMatrix_0;

        }
        else
        {
            gameData->RenderSlotArray[i]._2D = true;
            glm::mat4 ModelMatrix_0 = glm::mat4(1.0f);

            gameData->RenderSlotArray[i].Model = gameData->models.Plane.modelData;
            gameData->RenderSlotArray[i].NumAttributes = 1;
            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader;
            gameData->RenderSlotArray[i].ViewMatrix = glm::mat4(1.0f);

            if (i == gameData->NumberOfRenderSlots - 2)
            {
                gameData->RenderSlotArray[i].uniforms.Vec3.push_back({ "Color", glm::vec3(0.54f, 0.17f, 0.89f) });
                ModelMatrix_0 = RGU_Translate(ModelMatrix_0, 0.5f, -0.5f );
                ModelMatrix_0 = RGU_Scale(ModelMatrix_0, 0.3f, 0.3f);
            }
            else
            {
                gameData->RenderSlotArray[i].uniforms.Vec3.push_back({ "Color", glm::vec3(0.30f, 0.13f, 0.85f) });
                ModelMatrix_0 = RGU_Translate(ModelMatrix_0, 0.8f, -0.8f );
                ModelMatrix_0 = RGU_Scale(ModelMatrix_0, 0.1f, 0.1f);

            }

            gameData->RenderSlotArray[i].ModelMatrix = ModelMatrix_0;
        }
    }
}

void GameFrame(GLFWwindow* window, GameData* gameData, float DeltaTime)
{
    for (unsigned int i = 0; i < gameData->NumberOfRenderSlots; ++i)
    {
        gameData->RenderSlotArray[i].Draw = true;
    }
}
