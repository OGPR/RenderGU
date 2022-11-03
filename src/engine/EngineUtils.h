#pragma once

#include "../Utility.h"

void EngineCleanUp(struct EngineVariables* engineVariables)
{
    free(engineVariables->RenderObjectSlotArray);
    engineVariables->RenderObjectSlotArray = nullptr;
}

int IntegerToTextureUnit(unsigned int Integer)
{
    if (Integer > 15) return -1;

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

    // Silence warning g++
    else return -1;
};


// Load game data will include vertex specification, shader compilation
void LoadGame(struct GameData* gameData,
        void(*GameInitFuncPtr)(struct GameData*),
        struct EngineVariables* engineVariables,
        GLFWwindow* window)
{
    (*GameInitFuncPtr)(gameData);

    const unsigned int NumberOfSlots = gameData->NumberOfRenderSlots;

    engineVariables->NumberOfSlots = NumberOfSlots;

    assert(engineVariables->NumberOfSlots);

    engineVariables->RenderObjectSlotArray =
        (EngineVariables::RenderObjectSlot*)calloc(engineVariables->NumberOfSlots, sizeof(EngineVariables::RenderObjectSlot));

    for (unsigned int i = 0; i < NumberOfSlots; ++i)
    {
        BindVBO(CreateVBO());

        // Only allocate what is needed
         
        //TODO handle this for dev/release build 
        // Will crash if these are zero
        assert(gameData->RenderSlotArray[i].Model.VBOMemoryAllocationSize_PosOnly);
        assert(gameData->RenderSlotArray[i].Model.VBOMemoryAllocationSize);

        if (!gameData->RenderSlotArray[i].Texture)
            AllocateMemoryVBO(gameData->RenderSlotArray[i].Model.VBOMemoryAllocationSize_PosOnly, gameData->RenderSlotArray[i].Model.VertexData);
        else
            AllocateMemoryVBO(gameData->RenderSlotArray[i].Model.VBOMemoryAllocationSize, gameData->RenderSlotArray[i].Model.VertexData);

        unsigned int VAO = CreateVAO();
        BindVAO(VAO);

        const unsigned int NumAttributes = gameData->RenderSlotArray[i].NumAttributes;

        //TODO handle this for dev/release build 
        assert(NumAttributes); // Won't have anything rendered if NumAttributes is zero

        assert(gameData->RenderSlotArray[i].Model.AttributeArray);
        for (unsigned int j = 0; j < NumAttributes;++j)
        {
            SetAttribute(j,
                    gameData->RenderSlotArray[i].Model.AttributeArray[j].Size,
                    gameData->RenderSlotArray[i].Model.AttributeArray[j].Stride,
                    gameData->RenderSlotArray[i].Model.AttributeArray[j].Offset);
        }



        if (gameData->RenderSlotArray[i].Model.IndexArray)
        {
            engineVariables->RenderObjectSlotArray[i].IndexedDraw = true;

            unsigned int EBO;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(
                    GL_ELEMENT_ARRAY_BUFFER,
                    gameData->RenderSlotArray[i].Model.EBOMemoryAllocationSize,
                    gameData->RenderSlotArray[i].Model.IndexArray,
                    GL_STATIC_DRAW);
        }


        engineVariables->RenderObjectSlotArray[i].VAO = VAO;
        engineVariables->RenderObjectSlotArray[i].Indices = gameData->RenderSlotArray[i].Model.Indices;
        
        // Link the shaders
        const char* vs = gameData->RenderSlotArray[i].VertexShader;

        if (!vs)
        {
            printf("Vertex shader required\n");
            return;
        }

        const char* fs = gameData->RenderSlotArray[i].FragmentShader;

        if (!fs)
        {
            printf("Fragment shader required\n");
            return;
        }


        unsigned int shaderProgram;
        
        bool GLSLFormat = vs[0] == '#';

        if (engineVariables->GLSLCompile)
        {
            if (!GLSLFormat)
            {
                printf("\n\n!!!--------------------------------------------------------------------------------------------------!!!\n");
                printf("RenderGU says...\n");
                printf("It is possible that have specified a SPIR-V binary...\n");
                printf("If this is the case, provide the shader in GLSL string form or compile in SPIR-V mode (default)...\n");
                printf("!!!----------------------------------------------------------------------------------------------------!!!\n\n");
            }

            shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));
        }
        else
        {
            if (GLSLFormat)
            {
                printf("\n\n!!!--------------------------------------------------------------------------------!!!\n");
                printf("RenderGU says...\n");
                printf("It is possible that have not specified a SPIR-V binary...\n");
                printf("If this is the case, either provide a SPIR-V binary or compile in GLSL mode (-gl)...\n");
                printf("!!!----------------------------------------------------------------------------------!!!\n\n");
            }

            shaderProgram = linkShaders(createVertexShader(vs), createFragmentShader(fs));
        }
        
        // End linking shaders

        engineVariables->RenderObjectSlotArray[i].ShaderProgram = shaderProgram;

        engineVariables->RenderObjectSlotArray[i].ModelMatrix = &gameData->RenderSlotArray[i].ModelMatrix;
        engineVariables->RenderObjectSlotArray[i].ViewMatrix = &gameData->RenderSlotArray[i].ViewMatrix;
        engineVariables->RenderObjectSlotArray[i].ProjectionMatrix = &gameData->RenderSlotArray[i].ProjectionMatrix;

        engineVariables->RenderObjectSlotArray[i].DepthTest = gameData->RenderSlotArray[i].DepthTest;

        ///---START Texture setting ---///
        const char* TextureRelPathname = gameData->RenderSlotArray[i].Texture;
        if (TextureRelPathname)
        {

            int img_width, img_height, img_nChannels;
            unsigned char* img_data = stbi_load(TextureRelPathname,
                    &img_width, &img_height, &img_nChannels,0);

            if (!img_data)
            {
                // TODO fix for MSVC
#if !_MSC_VER
                char cwd[PATH_MAX];
                if (!getcwd(cwd, sizeof(cwd)))
                    printf("\ngetcwd error\n");

                printf("Failed to load texture...%s\n", TextureRelPathname);
                printf("We are currently in %s\n", cwd);
#endif
            }

            unsigned int texture;
            glGenTextures(1,&texture);

            engineVariables->RenderObjectSlotArray[i].TextureID = texture; 
            engineVariables->RenderObjectSlotArray[i].TextureUnit = gameData->RenderSlotArray[i].TextureArrayIndex;

            int TextureUnit = IntegerToTextureUnit(gameData->RenderSlotArray[i].TextureArrayIndex);

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

        ///---START Uniform assignment from game data ---///

        engineVariables->RenderObjectSlotArray[i].uniforms.Vec3 = gameData->RenderSlotArray[i].uniforms.Vec3;
        ///---END Uniform assignment from game data ---///


    }

}

