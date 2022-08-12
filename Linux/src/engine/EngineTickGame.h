#pragma once

#include "../Utility.h"
#include "EngineVariables.h"

void TickGame(GLFWwindow* window,
        EngineVariables* engineVariables,
        struct GameData* gameData,
        void(*GameTickFuncPtr)(GLFWwindow*, struct GameData*))
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(engineVariables->shaderProgram);
    glBindVertexArray(engineVariables->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    (*GameTickFuncPtr)(window, gameData); 
}
