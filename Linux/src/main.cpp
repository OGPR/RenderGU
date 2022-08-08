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
#include "engine/EngineInputProcessing.h"
#include "engine/EngineEndFrame.h"
#include "engine/EngineTickGame.h"


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

    // Initialise Game Data
    GameData gameData;

    while(!WindowShouldClose(window))
    {
        DeltaTime();

        EngineInputProcessing(window, &engineVariables);

        if (!engineVariables.pause)
        {
            TickGame(window, &gameData, &GameFrame);

            EngineEndFrame(window, &engineVariables, false);
        }

    }
    
    // Exit
    Terminate();
    return 0;
}
