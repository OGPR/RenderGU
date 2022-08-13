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
#include "games/BaselineTriangle/Triangle.h"
#include "engine/EngineVariables.h"
#include "engine/EngineInputProcessing.h"
#include "engine/EngineEndFrame.h"
#include "engine/EngineTickGame.h"

// Load game data will include vertex specification, shader compilation
void LoadGame(struct GameData* gameData, EngineVariables* engineVariables)
{
    // Specify the vertices based on gameData model
    BindVBO(CreateVBO());
    AllocateMemoryVBO(15, gameData->shadersToModelAssignment.slot1.Model);
    unsigned int VAO = CreateVAO();
    BindVAO(VAO);
    SetAttribute(0, 3, 0, (void*)0);

    engineVariables->renderObjectSlot1.VAO = VAO;
    engineVariables->renderObjectSlot1.Indices = gameData->shadersToModelAssignment.slot1.ModelIndices;
    
    // Compile the shaders
    const char* vs = gameData->shadersToModelAssignment.slot1.VertexShader;
    const char* fs = gameData->shadersToModelAssignment.slot1.FragmentShader;

    unsigned int shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

    engineVariables->renderObjectSlot1.ShaderProgram = shaderProgram;

    engineVariables->renderObjectSlot1.ModelMatrix = &gameData->shadersToModelAssignment.slot1.ModelMatrix;
    engineVariables->renderObjectSlot1.ViewMatrix = &gameData->shadersToModelAssignment.slot1.ViewMatrix;
    engineVariables->renderObjectSlot1.ProjectionMatrix = &gameData->shadersToModelAssignment.slot1.ProjectionMatrix;
}

int main()
{
    // Create main window
    GLFWwindow* window = Window();

    // Initialise Engine Variables
    EngineVariables engineVariables;

    // Initialise Game Data
    GameData gameData;

    LoadGame(&gameData, &engineVariables);
   
    

    while(!WindowShouldClose(window))
    {
        DeltaTime();

        EngineInputProcessing(window, &engineVariables);

        if (!engineVariables.pause)
        {
            TickGame(window, &engineVariables, &gameData, &GameFrame);

            EngineEndFrame(window, &engineVariables, false);
        }

    }
    
    // Exit
    Terminate();
    return 0;
}
