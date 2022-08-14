#pragma once

#include "../Utility.h"
#include "EngineVariables.h"

void TickGame(GLFWwindow* window,
        EngineVariables* engineVariables,
        struct GameData* gameData,
        void(*GameTickFuncPtr)(GLFWwindow*, struct GameData*))
{
    (*GameTickFuncPtr)(window, gameData); 

    glClear(GL_COLOR_BUFFER_BIT);

   
    const unsigned int LoopMax = gameData->shadersToModelAssignment.NumberOfSlots;

    for (int i = 0; i < LoopMax; ++i)
    {
        if (gameData->shadersToModelAssignment.SlotArray[i].Draw)
        {
            glUseProgram(engineVariables->RenderObjectSlotArray[i].ShaderProgram);

            unsigned int ShaderProgram = engineVariables->RenderObjectSlotArray[0].ShaderProgram;

            glm::mat4 ModelMatrix = *engineVariables->RenderObjectSlotArray[i].ModelMatrix;
            glm::mat4 ViewMatrix = *engineVariables->RenderObjectSlotArray[i].ViewMatrix;
            glm::mat4 ProjectionMatrix = *engineVariables->RenderObjectSlotArray[i].ProjectionMatrix;

            glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
            glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
            glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

            glBindVertexArray(engineVariables->RenderObjectSlotArray[i].VAO);
            glDrawArrays(GL_TRIANGLES, 0, engineVariables->RenderObjectSlotArray[i].Indices);
        }

    }

}
