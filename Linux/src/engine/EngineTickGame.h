#pragma once

#include "../Utility.h"

void TickGame(GLFWwindow* window,
        unsigned int* shaderProgram,
        unsigned int* VAO,
        struct GameData* gameData,
        void(*GameTickFuncPtr)(GLFWwindow*, struct GameData*))
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    (*GameTickFuncPtr)(window, gameData); 
}
