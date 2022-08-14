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

        unsigned int ShaderProgram_Slot1 = engineVariables->renderObjectSlot1.ShaderProgram;

        glm::mat4 ModelMatrix_Slot1 = *engineVariables->renderObjectSlot1.ModelMatrix;
        glm::mat4 ViewMatrix_Slot1 = *engineVariables->renderObjectSlot1.ViewMatrix;
        glm::mat4 ProjectionMatrix_Slot1 = *engineVariables->renderObjectSlot1.ProjectionMatrix;

        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram_Slot1, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix_Slot1));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram_Slot1, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix_Slot1));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram_Slot1, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix_Slot1));

        glBindVertexArray(engineVariables->renderObjectSlot1.VAO);
        glDrawArrays(GL_TRIANGLES, 0, engineVariables->renderObjectSlot1.Indices);
    }

    if (gameData->shadersToModelAssignment.slot2.Draw)
    {
        glUseProgram(engineVariables->renderObjectSlot2.ShaderProgram);

        unsigned int ShaderProgram_Slot2 = engineVariables->renderObjectSlot2.ShaderProgram;

        glm::mat4 ModelMatrix_Slot2 = *engineVariables->renderObjectSlot2.ModelMatrix;
        glm::mat4 ViewMatrix_Slot2 = *engineVariables->renderObjectSlot2.ViewMatrix;
        glm::mat4 ProjectionMatrix_Slot2 = *engineVariables->renderObjectSlot2.ProjectionMatrix;

        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram_Slot2, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix_Slot2));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram_Slot2, "ViewMatrix"), 1, GL_FALSE, glm::value_ptr(ViewMatrix_Slot2));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram_Slot2, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix_Slot2));

        glBindVertexArray(engineVariables->renderObjectSlot2.VAO);
        glDrawArrays(GL_TRIANGLES, 0, engineVariables->renderObjectSlot2.Indices);
    }

}
