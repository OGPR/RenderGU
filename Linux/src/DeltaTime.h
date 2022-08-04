#pragma once

#include <GLFW/glfw3.h>

static float currFrameTime;
static float lastFrameTime = 0.f;
static float deltaTime;

void DeltaTime()
{
    currFrameTime = glfwGetTime();
    deltaTime = currFrameTime - lastFrameTime;
    lastFrameTime = currFrameTime;   
}
