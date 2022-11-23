//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================
#include "Window.h"
#include "Utility.h"
#include "CompileShaders.h"
#include "LinkShaders.h"
#include "DeltaTime.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"

//#include "games/BaselineTriangle/Triangle.h"
//#include "games/BaselinePlane/Plane.h"
//#include "games/BaselineCube/Cube.h"
//#include "games/BaselineLighting/Lighting.h"
//#include "test/Transformations/2D.h"
#include "test/Optimisations/VBO_OptimisationTest.h"

#include "engine/EngineVariables.h"
#include "engine/EngineInputProcessing.h"
#include "engine/EngineEndFrame.h"
#include "engine/EngineTickGame.h"
#include "engine/EngineUtils.h"
#include <time.h>


int main(int argc, char** argv)
{
    // Initialise Game Data (must be done before window creation to get window specs)
    GameData gameData;

    // Create main window
    GLFWwindow* window = Window(
            gameData.windowSpecification.WindowWidth,
            gameData.windowSpecification.WindowHeight,
            gameData.windowSpecification.WindowTitle,
            gameData.windowSpecification.WindowXPos,
            gameData.windowSpecification.WindowYPos);

    // Set callbacks
    SetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialise Engine Variables
    EngineVariables engineVariables;
    engineVariables.GLSLCompile = argc == 2 && !strcmp(argv[1], "-gl");
    


    clock_t ClockBegin = clock();
    LoadGame(&gameData, &GameInit, &engineVariables, window);
    clock_t ClockEnd = clock();
    double Time_ms = ((double) (ClockEnd - ClockBegin) / CLOCKS_PER_SEC) * 1000;
    printf("Time: %f ms\n", Time_ms);

    // Engine delta time
    float DeltaTime = 0;

    // WindowPos variables
    int WindowWidth, WindowHeight;
    glfwGetWindowSize(window, &WindowWidth, &WindowHeight);
    glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    while(!WindowShouldClose(window))
    {
        UpdateDeltaTime(&DeltaTime);

        EngineInputProcessing(window, &engineVariables);

        if (!engineVariables.pause)
        {
            TickGame(window, &engineVariables, &gameData, DeltaTime, &WindowWidth, &WindowHeight, &GameFrame);

            EngineEndFrame(window, &engineVariables, false, DeltaTime);
        }
    }
    
    // Exit
    EngineCleanUp(&engineVariables);
    Terminate();
    return 0;
}
