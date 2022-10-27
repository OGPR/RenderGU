#pragma once

#include <GLFW/glfw3.h>

static float currFrameTime;
static float lastFrameTime = 0.f;

float DeltaTime()
{
    float deltaTime;
    currFrameTime = glfwGetTime();
    deltaTime = currFrameTime - lastFrameTime;
    lastFrameTime = currFrameTime;
    return deltaTime;
}
