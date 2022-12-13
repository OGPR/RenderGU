#pragma once

#include "../Utility.h"
#include "EngineVariables.h"
#include "EngineUtils.h"
#include <iostream>
#include <vector>

void TickGame(GLFWwindow* window,
              EngineVariables* engineVariables,
              struct GameData* gameData,
              float DeltaTime,
              int* WindowWidth,
              int* WindowHeight,
              void(*GameTickFuncPtr)(GLFWwindow*, struct GameData*, float DeltaTime),
        std::vector<std::vector<bool>> &SlotErrorReported)
{
    (*GameTickFuncPtr)(window, gameData, DeltaTime);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   
    const unsigned int LoopMax = gameData->NumberOfRenderSlots;
    assert(SlotErrorReported.size() == LoopMax);
    for (auto& Elem : SlotErrorReported)
    {
        assert(Elem.size() == 3);
    }

    for (unsigned int i = 0; i < LoopMax; ++i)
    {
        if (gameData->RenderSlotArray[i].Draw)
        {
            if (engineVariables->RenderObjectSlotArray[i].DepthTest)
                glEnable(GL_DEPTH_TEST);

            glUseProgram(engineVariables->RenderObjectSlotArray[i].ShaderProgram);

            unsigned int ShaderProgram = engineVariables->RenderObjectSlotArray[i].ShaderProgram;

            glm::mat4 ModelMatrix = *engineVariables->RenderObjectSlotArray[i].ModelMatrix;
            glm::mat4 ViewMatrix = *engineVariables->RenderObjectSlotArray[i].ViewMatrix;

            processWindowPos(window, WindowWidth, WindowHeight);
            float OrthWidth = *WindowWidth / float(gameData->windowSpecification.WindowWidth);
            float OrthHeight = *WindowHeight / float(gameData->windowSpecification.WindowHeight);
            glm::mat4 ProjectionMatrix = engineVariables->RenderObjectSlotArray[i]._2D ?
                    glm::ortho(-OrthWidth, OrthWidth, -OrthHeight, OrthHeight, 0.0f, 0.01f) :
                    glm::perspective(glm::radians(45.f), float(*WindowWidth) / float(*WindowHeight), 0.1f, 100.f);

            SetTransformMatrixUniforms(ShaderProgram,
                                       ModelMatrix,
                                       ViewMatrix,
                                       ProjectionMatrix,
                                       engineVariables->transformMatrixUniformNames.ModelMatrixUniformName,
                                       engineVariables->transformMatrixUniformNames.ViewMatrixUniformName,
                                       engineVariables->transformMatrixUniformNames.ViewMatrixUniformName,
                                       SlotErrorReported,
                                       i,
                                       gameData);

            for (const auto& UniformPair : *engineVariables->RenderObjectSlotArray[i].uniforms.Vec3)
            {
                if (glGetUniformLocation(ShaderProgram, UniformPair.first) != -1)
                {
					glUniform3fv(glGetUniformLocation(
						ShaderProgram,
						UniformPair.first),
						1,
						&UniformPair.second[0]);
                }
                else 
                {
                    std::cout << UniformPair.first << " shader uniform name not present" << std::endl;
                    std::cout << "RenderGU is currently processing render slot " << i << " during tick" << std::endl;
                }
            }

            for (const auto& UniformPair : *engineVariables->RenderObjectSlotArray[i].uniforms.Float)
            {
                if (glGetUniformLocation(ShaderProgram, UniformPair.first) != -1)
                {
                    glUniform1f(glGetUniformLocation(
                        ShaderProgram,
                        UniformPair.first),
                        UniformPair.second);
                }
                else 
                {
                    std::cout << UniformPair.first << " shader uniform name not present" << std::endl;
                    std::cout << "RenderGU is currently processing render slot " << i << " during tick" << std::endl;
                }
            }

            if (gameData->RenderSlotArray[i].Texture)
            {
                glUniform1i(glGetUniformLocation(ShaderProgram, "Texture"), engineVariables->RenderObjectSlotArray[i].TextureUnit);
            }

            glBindVertexArray(engineVariables->RenderObjectSlotArray[i].VAO);

            if (engineVariables->RenderObjectSlotArray[i].IndexedDraw)
                glDrawElements(GL_TRIANGLES,engineVariables->RenderObjectSlotArray[i].Indices, GL_UNSIGNED_INT, 0);
            else
                glDrawArrays(GL_TRIANGLES, 0, engineVariables->RenderObjectSlotArray[i].Indices);

            if (engineVariables->RenderObjectSlotArray[i].DepthTest)
                glDisable(GL_DEPTH_TEST);
        }

    }

}
