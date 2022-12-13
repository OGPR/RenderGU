#pragma once

#include "../Utility.h"
#include "EngineVariables.h"
#include <iostream>
#include <vector>

static void HandleUniformNameError(const char* UniformName, const char* ShaderFile, unsigned int SlotNumber)
{
    std::cout << "\nRenderGU requires a shader uniform named \"" << UniformName << "\"" << std::endl;
    std::cout << "See shader " << ShaderFile << std::endl;
    std::cout << "RenderGU is currently processing render slot " << SlotNumber << " during tick\n" << std::endl;

}
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

            /// --- START Transform matrix uniform setting --- ///

            const char* ModelMatUniformName = engineVariables->transformMatrixUniformNames.ModelMatrixUniformName;
            const char* ViewMatUniformName = engineVariables->transformMatrixUniformNames.ViewMatrixUniformName;
            const char* ProjMatUniformName = engineVariables->transformMatrixUniformNames.ProjectionMatrixUniformName;

            // Model Matrix Uniform
            GLint LocModelMatUniform = glGetUniformLocation(ShaderProgram, ModelMatUniformName);
            if (LocModelMatUniform != -1)
            {
                glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, ModelMatUniformName), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
            }
            else if (!SlotErrorReported[i][0])
            {
                SlotErrorReported[i][0] = true;
                HandleUniformNameError(ModelMatUniformName, gameData->RenderSlotArray[i].VertexShader, i);
            }

            // View Matrix Uniform
            GLint LocViewMatUniform = glGetUniformLocation(ShaderProgram, ViewMatUniformName);
            if (LocViewMatUniform != -1)
            {
                glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, ViewMatUniformName), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
            }
            else if (!SlotErrorReported[i][1])
            {
                SlotErrorReported[i][1] = true;
                HandleUniformNameError(ViewMatUniformName, gameData->RenderSlotArray[i].VertexShader, i);
            }

            // Projection Matrix Uniform
            GLint LocProjMatUniform = glGetUniformLocation(ShaderProgram, ProjMatUniformName);
            if (LocProjMatUniform != -1)
            {
                glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, ProjMatUniformName), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
            }
            else if (!SlotErrorReported[i][2])
            {
                SlotErrorReported[i][2] = true;
                HandleUniformNameError(ProjMatUniformName, gameData->RenderSlotArray[i].VertexShader, i);
            }

            /// --- END Transform matrix uniform setting --- ///

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
