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
    ///---START Slot1---/// 
    BindVBO(CreateVBO());
    AllocateMemoryVBO(15, gameData->shadersToModelAssignment.slot1.Model);
    unsigned int VAO_Slot1 = CreateVAO();
    BindVAO(VAO_Slot1);
    SetAttribute(0, 3, 0, (void*)0);

    engineVariables->renderObjectSlot1.VAO = VAO_Slot1;
    engineVariables->renderObjectSlot1.Indices = gameData->shadersToModelAssignment.slot1.ModelIndices;
    
    // Compile the shaders
    const char* vs_Slot1 = gameData->shadersToModelAssignment.slot1.VertexShader;
    const char* fs_Slot1 = gameData->shadersToModelAssignment.slot1.FragmentShader;

    unsigned int shaderProgram_Slot1 = linkShaders(compileVertexShader(vs_Slot1), compileFragmentShader(fs_Slot1));

    engineVariables->renderObjectSlot1.ShaderProgram = shaderProgram_Slot1;

    engineVariables->renderObjectSlot1.ModelMatrix = &gameData->shadersToModelAssignment.slot1.ModelMatrix;
    engineVariables->renderObjectSlot1.ViewMatrix = &gameData->shadersToModelAssignment.slot1.ViewMatrix;
    engineVariables->renderObjectSlot1.ProjectionMatrix = &gameData->shadersToModelAssignment.slot1.ProjectionMatrix;
    ///---END Slot1---/// 
    
    ///---START Slot2---/// 
    BindVBO(CreateVBO());
    AllocateMemoryVBO(15, gameData->shadersToModelAssignment.slot2.Model);
    unsigned int VAO_Slot2 = CreateVAO();
    BindVAO(VAO_Slot2);
    SetAttribute(0, 3, 0, (void*)0);

    engineVariables->renderObjectSlot2.VAO = VAO_Slot2;
    engineVariables->renderObjectSlot2.Indices = gameData->shadersToModelAssignment.slot2.ModelIndices;
    
    // Compile the shaders
    const char* vs_Slot2 = gameData->shadersToModelAssignment.slot2.VertexShader;
    const char* fs_Slot2 = gameData->shadersToModelAssignment.slot2.FragmentShader;

    unsigned int shaderProgram_Slot2 = linkShaders(compileVertexShader(vs_Slot2), compileFragmentShader(fs_Slot2));

    engineVariables->renderObjectSlot2.ShaderProgram = shaderProgram_Slot2;

    engineVariables->renderObjectSlot2.ModelMatrix = &gameData->shadersToModelAssignment.slot2.ModelMatrix;
    engineVariables->renderObjectSlot2.ViewMatrix = &gameData->shadersToModelAssignment.slot2.ViewMatrix;
    engineVariables->renderObjectSlot2.ProjectionMatrix = &gameData->shadersToModelAssignment.slot2.ProjectionMatrix;
    ///---END Slot2---/// 
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
