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
void LoadGame(struct GameData* gameData,
        void(*GameInitFuncPtr)(struct GameData*),
        EngineVariables* engineVariables)
{
    (*GameInitFuncPtr)(gameData);

    const unsigned int LoopMax = gameData->shadersToModelAssignment.NumberOfSlots;

    for (int i = 0; i < LoopMax; ++i)
    {
        BindVBO(CreateVBO());
        AllocateMemoryVBO(15, gameData->shadersToModelAssignment.SlotArray[i].Model);
        unsigned int VAO = CreateVAO();
        BindVAO(VAO);
        SetAttribute(0, 3, 0, (void*)0);
        
        // TODO do we want to do this only if we have a tex? Could adjust VBO allocation also in that case.
        SetAttribute(1, 2, 0, (void*)(9 * sizeof(float))); 


        engineVariables->RenderObjectSlotArray[i].VAO = VAO;
        engineVariables->RenderObjectSlotArray[i].Indices = gameData->shadersToModelAssignment.SlotArray[i].ModelIndices;
        
        // Compile the shaders
        const char* vs = gameData->shadersToModelAssignment.SlotArray[i].VertexShader;
        const char* fs = gameData->shadersToModelAssignment.SlotArray[i].FragmentShader;

        unsigned int shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

        engineVariables->RenderObjectSlotArray[i].ShaderProgram = shaderProgram;

        engineVariables->RenderObjectSlotArray[i].ModelMatrix = &gameData->shadersToModelAssignment.SlotArray[i].ModelMatrix;
        engineVariables->RenderObjectSlotArray[i].ViewMatrix = &gameData->shadersToModelAssignment.SlotArray[i].ViewMatrix;
        engineVariables->RenderObjectSlotArray[i].ProjectionMatrix = &gameData->shadersToModelAssignment.SlotArray[i].ProjectionMatrix;

        if(gameData->shadersToModelAssignment.SlotArray[i].Texture)
        {
            int img_width, img_height, img_nChannels;
            unsigned char* img_data = stbi_load("resources/container.jpg", &img_width, &img_height, &img_nChannels,0);

            if (!img_data)
                    printf("Failed to load texture...");

            unsigned int texture;
            glGenTextures(1,&texture);

            engineVariables->RenderObjectSlotArray[i].TextureTarget = texture; 

            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(img_data);
        }

    }

}

int main()
{
    // Create main window
    GLFWwindow* window = Window();

    // Initialise Engine Variables
    EngineVariables engineVariables;

    // Initialise Game Data
    GameData gameData;

    LoadGame(&gameData, &GameInit, &engineVariables);
   
    

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
