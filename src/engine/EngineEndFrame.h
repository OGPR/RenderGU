#pragma once

#include "EngineVariables.h"
#include "../Utility.h"

void EngineEndFrame(GLFWwindow* window, EngineVariables* engineVariables, bool ShowEngineFrameTime, float DeltaTime)
{
    //// check and call events, and swap buffers
    PollEvents();


    ++engineVariables->frameNumber;

    if (ShowEngineFrameTime)
    {

        if (engineVariables->frameNumber < 11)
            printf("Engine Frame Time:  %f ms\n", DeltaTime * 1000.0f);
        else
            printf("\rEngine Frame Time:  %f ms", DeltaTime * 1000.0f);
        fflush(stdout);
    }


    SwapBuffers(window);
}

