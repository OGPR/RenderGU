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
        glBindVertexArray(engineVariables->renderObjectSlot1.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }


}
