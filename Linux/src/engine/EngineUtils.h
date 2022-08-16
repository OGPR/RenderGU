#pragma once

#include "../Utility.h"

int IntegerToTextureUnit(unsigned int Integer)
{
    if (Integer == 0) return GL_TEXTURE0;
    if (Integer == 1) return GL_TEXTURE1;
    if (Integer == 2) return GL_TEXTURE2;
    if (Integer == 3) return GL_TEXTURE3;
    if (Integer == 4) return GL_TEXTURE4;
    if (Integer == 5) return GL_TEXTURE5;
    if (Integer == 6) return GL_TEXTURE6;
    if (Integer == 7) return GL_TEXTURE7;
    if (Integer == 8) return GL_TEXTURE8;
    if (Integer == 9) return GL_TEXTURE9;
    if (Integer == 10) return GL_TEXTURE10;
    if (Integer == 11) return GL_TEXTURE11;
    if (Integer == 12) return GL_TEXTURE12;
    if (Integer == 13) return GL_TEXTURE13;
    if (Integer == 14) return GL_TEXTURE14;
    if (Integer == 15) return GL_TEXTURE15;

    else return -1;
};

// Load game data will include vertex specification, shader compilation
void LoadGame(struct GameData* gameData,
        void(*GameInitFuncPtr)(struct GameData*),
        struct EngineVariables* engineVariables)
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

        ///---START Texture setting ---///
        const char* TextureRelPathname = gameData->shadersToModelAssignment.SlotArray[i].Texture;
        if (TextureRelPathname)
        {

            int img_width, img_height, img_nChannels;
            unsigned char* img_data = stbi_load(TextureRelPathname,
                    &img_width, &img_height, &img_nChannels,0);

            if (!img_data)
                    printf("Failed to load texture...%s\n", TextureRelPathname);

            unsigned int texture;
            glGenTextures(1,&texture);

            engineVariables->RenderObjectSlotArray[i].TextureID = texture; 
            engineVariables->RenderObjectSlotArray[i].TextureUnit = gameData->shadersToModelAssignment.SlotArray[i].TextureArrayIndex;

            int TextureUnit = IntegerToTextureUnit(gameData->shadersToModelAssignment.SlotArray[i].TextureArrayIndex);

            if (TextureUnit == -1)
            {
                printf("Error in RenderGU_IntegerToTextureUnit function\n");
            }
            else
            {
                glActiveTexture(TextureUnit);
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
        ///---END Texture setting ---///

    }

}
