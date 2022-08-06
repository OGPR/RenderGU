#pragma once

#include "EngineVariables.h"
#include "../Utility.h"

void EngineEndFrame(GLFWwindow* window, EngineVariables* engineVariables)
{
    //// check and call events, and swap buffers
    PollEvents();


    ++engineVariables->frameNumber;
    if (engineVariables->frameNumber < 11)
        printf("Frame Time:  %f ms\n", deltaTime * 1000.0f);
    else
        printf("\rFrame Time:  %f ms", deltaTime * 1000.0f);
    fflush(stdout);


    SwapBuffers(window);
}

