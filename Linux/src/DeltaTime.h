#pragma once

#include <GLFW/glfw3.h>

static float currFrameTime;
static float lastFrameTime = 0.f;

void UpdateDeltaTime(float* DeltaTime)
{
    currFrameTime = glfwGetTime();
    *DeltaTime = currFrameTime - lastFrameTime;
    lastFrameTime = currFrameTime;   
}
