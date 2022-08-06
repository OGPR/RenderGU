//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================


//macro to write shader programs inline
#ifndef GLSL 
#define GLSL(version,A) "#version " #version "\n" #A
#endif

#include "Window.h"
#include "Utility.h"
#include "CompileShaders.h"
#include "LinkShaders.h"
#include "DeltaTime.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "scenes/BarycentricTriangle.h"
#include "scenes/Camera3D.h"
#include "models/cube/model.h"
#include "Camera.h"
#include "games/TransitionAndMenuShowcase/Game.h"
#include "engine/EngineVariables.h"


// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}


int main()
{
    // Create main window
    GLFWwindow* window = Window();

    // Initialise Engine Variables
    EngineVariables engineVariables;

    while(!WindowShouldClose(window))
    {
         DeltaTime();
        
        //---START Engine input processing
         if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         {
            glfwSetWindowShouldClose(window, true);
         }

         if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !engineVariables.space_pressed)
         {
             engineVariables.space_pressed = true;
             engineVariables.pause = !engineVariables.pause;
         }

         if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && engineVariables.space_pressed)
         {
             engineVariables.space_pressed = false;
         }

         if (engineVariables.pause)
         {
             PollEvents();
             continue;
         }
        //---END Engine input processing

         Play(window, &engineVariables.frameNumber, &DisplayState);
        
        ///---START Engine Code---///
        //// check and call events, and swap buffers
        PollEvents();


        ++engineVariables.frameNumber;
        if (engineVariables.frameNumber < 11)
            printf("Frame Time:  %f ms\n", deltaTime * 1000.0f);
        else
            printf("\rFrame Time:  %f ms", deltaTime * 1000.0f);
        fflush(stdout);
        ///---END Engine Code---///


        SwapBuffers(window);
    }

    // Exit
    Terminate();
    return 0;
}
