//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================


#include "Window.h"
#include "Rendering_Common.h"
#include "scenes/CubeGrassWindowFloor/scene_render.h"
#include "scenes/Skybox/scene_render.h"

// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}

int main()
{
    GLFWwindow* window = Window();

    
    //SceneRender_CubeGrassWindowFloor(window);
    SceneRender_Skybox(window);

    Terminate();
    return 0;





}
