#pragma once

#include "EngineVariables.h"
#include "../Utility.h"

void EngineEndFrame(GLFWwindow* window, EngineVariables* engineVariables, bool ShowEngineFrameTime)
{
    //// check and call events, and swap buffers
    PollEvents();


    ++engineVariables->frameNumber;

    if (ShowEngineFrameTime)
    {

        if (engineVariables->frameNumber < 11)
            printf("Engine Frame Time:  %f ms\n", deltaTime * 1000.0f);
        else
            printf("\rEngine Frame Time:  %f ms", deltaTime * 1000.0f);
        fflush(stdout);
    }


    SwapBuffers(window);
}

