#pragma once

#include "EngineVariables.h"
#include "../Utility.h"

void EngineInputProcessing(GLFWwindow* window, EngineVariables* engineVariables)
{
     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
     {
        glfwSetWindowShouldClose(window, true);
     }

     if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !engineVariables->space_pressed)
     {
         engineVariables->space_pressed = true;
         engineVariables->pause = !engineVariables->pause;
     }

     if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && engineVariables->space_pressed)
     {
         engineVariables->space_pressed = false;
     }

     if (engineVariables->pause)
     {
         PollEvents();
     }
}

