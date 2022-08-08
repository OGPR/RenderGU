#pragma once

#include "../Utility.h"

void TickGame(GLFWwindow* window, struct GameData* gameData, void(*GameTickFuncPtr)(GLFWwindow*, struct GameData*))
{
    (*GameTickFuncPtr)(window, gameData); 
}
