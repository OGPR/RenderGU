#pragma once

#include "../Utility.h"
#include "EngineVariables.h"

void TickGame(GLFWwindow* window,
        EngineVariables* engineVariables,
        struct GameData* gameData,
        float DeltaTime,
        void(*GameTickFuncPtr)(GLFWwindow*, struct GameData*, float DeltaTime))
{
    (*GameTickFuncPtr)(window, gameData, DeltaTime); 

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   
    const unsigned int LoopMax = gameData->NumberOfRenderSlots;

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
            glm::mat4 ProjectionMatrix = *engineVariables->RenderObjectSlotArray[i].ProjectionMatrix;

            // TODO check/handle Unifrom existence 
            glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
            glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
            glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

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
