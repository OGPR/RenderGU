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

   
    if (gameData->shadersToModelAssignment.slot1.Draw)
    {
        glUseProgram(engineVariables->renderObjectSlot1.ShaderProgram);

        unsigned int ShaderProgram = engineVariables->renderObjectSlot1.ShaderProgram;

        glm::mat4 ModelMatrix = *engineVariables->renderObjectSlot1.ModelMatrix;
        glm::mat4 ViewMatrix = *engineVariables->renderObjectSlot1.ViewMatrix;
        glm::mat4 ProjectionMatrix = *engineVariables->renderObjectSlot1.ProjectionMatrix;

        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

        glBindVertexArray(engineVariables->renderObjectSlot1.VAO);
        glDrawArrays(GL_TRIANGLES, 0, engineVariables->renderObjectSlot1.Indices);
    }

}
