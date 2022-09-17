#pragma once

#include "../../Utility.h"
#include "../../engine/GameUtils.h"
#include "../../engine/EngineBasicShapes.h"


struct GameData
{
    
    struct Models
    {
        EngineBasicShapes::Triangle Triangle;

    }models;

    struct Textures
    {
        
        const char* TextureArray [2] =
        {
            "resources/container.jpg",
            "resources/wall.jpg",
        };

    }textures;


    struct Shaders
    {
            const char* VertexShader = 
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;

            uniform mat4 ModelMatrix;
            uniform mat4 ViewMatrix;
            uniform mat4 ProjectionMatrix;

            void main()
            {
                gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inPos, 1.0f);
            }
            );

            const char* FragmentShader = 
            GLSL(330 core,
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(0.1f, 0.2f, 0.3f, 1.0f);
            }
            );

            // Tex coord passthrough VS
            const char* VertexShader_Tex = 
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;

            out vec2 TexCoord;

            uniform mat4 ModelMatrix;
            uniform mat4 ViewMatrix;
            uniform mat4 ProjectionMatrix;

            void main()
            {
                gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inPos, 1.0f);
                TexCoord = inTexCoord;

            }
            );

            const char* FragmentShader_Tex = 
            GLSL(330 core,
            out vec4 FragColor;
            in vec2 TexCoord;

            uniform sampler2D Texture;

            void main()
            {
                FragColor = texture(Texture, TexCoord);
            }
            );
            
            // Tex coord passthrough VS
            const char* VertexShader_Tex2 = 
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;

            out vec2 TexCoord;

            uniform mat4 ModelMatrix;
            uniform mat4 ViewMatrix;
            uniform mat4 ProjectionMatrix;

            void main()
            {
                gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inPos, 1.0f);
                TexCoord = inTexCoord;

            }
            );

            const char* FragmentShader_Tex2 = 
            GLSL(330 core,
            out vec4 FragColor;
            in vec2 TexCoord;

            uniform sampler2D Texture;

            void main()
            {
                FragColor = texture(Texture, TexCoord);
            }
            );

    }shaders;


    RenderSlot renderSlot1, renderSlot2, renderSlot3;

    unsigned int NumberOfRenderSlots = 3;
    RenderSlot RenderSlotArray[3] = {renderSlot1, renderSlot2, renderSlot3};

};

void GameInit(GameData* gameData)
{
    for (int i = 0; i < gameData->NumberOfRenderSlots; ++i)
    {
        glm::mat4 ModelMatrix_0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));

        if (i == 0)
        {
            gameData->RenderSlotArray[i].models = &gameData->models;
            gameData->RenderSlotArray[i].shaders = &gameData->shaders;
            gameData->RenderSlotArray[i].Model = gameData->models.Triangle.VertexData;
            gameData->RenderSlotArray[i].ModelIndices = gameData->models.Triangle.Indices;
            gameData->RenderSlotArray[i].ModelTextureCoordOffset = gameData->models.Triangle.TextureCoordOffset;
            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader;

            gameData->RenderSlotArray[i].ViewMatrix = glm::mat4(1.0f);  
            gameData->RenderSlotArray[i].ProjectionMatrix = glm::mat4(1.0f);
        }
        
        if(i == 0)
        {
            gameData->RenderSlotArray[i].ModelMatrix = glm::translate(
                    ModelMatrix_0,
                    glm::vec3(-1.0f, 0.0f, 0.0f));
        }


        if (i == 2)
        {
            gameData->RenderSlotArray[i].models = &gameData->models;
            gameData->RenderSlotArray[i].shaders = &gameData->shaders;
            gameData->RenderSlotArray[i].Model = gameData->models.Triangle.VertexData;
            gameData->RenderSlotArray[i].ModelIndices = gameData->models.Triangle.Indices;
            gameData->RenderSlotArray[i].ModelTextureCoordOffset = gameData->models.Triangle.TextureCoordOffset;
            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader_Tex;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Tex;

            gameData->RenderSlotArray[i].TextureArrayIndex = 0;

            unsigned int TextureArrayIndex = gameData->RenderSlotArray[i].TextureArrayIndex;
            gameData->RenderSlotArray[i].Texture = gameData->textures.TextureArray[TextureArrayIndex]; 

            gameData->RenderSlotArray[i].ModelMatrix = glm::translate(
                    ModelMatrix_0,
                    glm::vec3(0.5f, 0.0f, 0.0f));
        }

        if (i == 1)
        {
            gameData->RenderSlotArray[i].models = &gameData->models;
            gameData->RenderSlotArray[i].shaders = &gameData->shaders;
            gameData->RenderSlotArray[i].Model = gameData->models.Triangle.VertexData;
            gameData->RenderSlotArray[i].ModelIndices = gameData->models.Triangle.Indices;
            gameData->RenderSlotArray[i].ModelTextureCoordOffset = gameData->models.Triangle.TextureCoordOffset;
            gameData->RenderSlotArray[i].VertexShader = gameData->shaders.VertexShader_Tex2;
            gameData->RenderSlotArray[i].FragmentShader = gameData->shaders.FragmentShader_Tex2;

            gameData->RenderSlotArray[i].TextureArrayIndex = 1;

            unsigned int TextureArrayIndex = gameData->RenderSlotArray[i].TextureArrayIndex;
            gameData->RenderSlotArray[i].Texture = gameData->textures.TextureArray[TextureArrayIndex]; 

            gameData->RenderSlotArray[i].ModelMatrix = glm::translate(
                    ModelMatrix_0,
                    glm::vec3(1.0f, 0.0f, 0.0f));
        }

    }

}


void GameFrame(GLFWwindow* window, GameData* gameData)
{
    gameData->RenderSlotArray[0].Draw = true;
    gameData->RenderSlotArray[1].Draw = true;
    gameData->RenderSlotArray[2].Draw = true;

}
