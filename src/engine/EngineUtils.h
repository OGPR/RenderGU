#pragma once

#include <set>
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


// FOR EBO + VBO optimisation
unsigned int EBO;
std::set<const char*> ModelNameSetVBO;
std::set<const char*> ModelNameSetEBO;

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
        // Bind VAO First
        unsigned int VAO = CreateVAO();
        BindVAO(VAO);

        assert(gameData->RenderSlotArray[i].Model.Name);
        if(ModelNameSetVBO.find(gameData->RenderSlotArray[i].Model.Name) == std::end(ModelNameSetVBO))
        {
            ModelNameSetVBO.insert((gameData->RenderSlotArray[i].Model.Name));
            BindVBO(CreateVBO());

            //TODO handle this for dev/release build
            // Will crash if these are zero
            assert(gameData->RenderSlotArray[i].Model.VBOMemoryAllocationSize);

            AllocateMemoryVBO(gameData->RenderSlotArray[i].Model.VBOMemoryAllocationSize, gameData->RenderSlotArray[i].Model.VertexData);
        }

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

        // TODO Add instancing buffer optimisation to VBO optimisation (including handling indexing)

        unsigned int ModelMatrixBuffer;
        glGenBuffers(1, & ModelMatrixBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, ModelMatrixBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * gameData->RenderSlotArray[i].ModelMatrixCollection.size(), gameData->RenderSlotArray[i].ModelMatrixCollection.data(), GL_STATIC_DRAW);
        engineVariables->RenderObjectSlotArray[i].ModelMatrixBuffer = ModelMatrixBuffer;

        // TODO Un-hardcode attribute number 3
        if (gameData->RenderSlotArray[i].ModelMatrixCollection.size() >= 2)
        {
            for (unsigned int k = 3; k < 7; k++)
            {
                SetAttribute_Instanced(k,
                             4,
                             sizeof(glm::mat4),
                             (void*)(sizeof(glm::vec4) * (k-3)));
            }

        }
        //TODO handle < 2 case (and if there is no model matrix set)


        if (gameData->RenderSlotArray[i].Model.IndexArray)
        {
            engineVariables->RenderObjectSlotArray[i].IndexedDraw = true;

            if (ModelNameSetEBO.find(gameData->RenderSlotArray[i].Model.Name) == std::end(ModelNameSetEBO))
            {
                // Don't populate the ModelNameSetEBO just yet...
                glGenBuffers(1, &EBO);
            }

            // We always need to bind an EBO to a currently bound VAO
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            if (ModelNameSetEBO.find(gameData->RenderSlotArray[i].Model.Name) == std::end(ModelNameSetEBO))
            {
                // Now we can populate the ModelNameSetEBO
                ModelNameSetEBO.insert(gameData->RenderSlotArray[i].Model.Name);

                glBufferData(
                        GL_ELEMENT_ARRAY_BUFFER,
                        gameData->RenderSlotArray[i].Model.EBOMemoryAllocationSize,
                        gameData->RenderSlotArray[i].Model.IndexArray,
                        GL_STATIC_DRAW);

            }
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

        // TODO handle case where we have a model matrix collection of size one (and no ModelMatrix)
        // or we also have a model matrix
        if (gameData->RenderSlotArray[i].ModelMatrixCollection.size() < 2)
        {
            engineVariables->RenderObjectSlotArray[i].ModelMatrix = &gameData->RenderSlotArray[i].ModelMatrix;
        }

        engineVariables->RenderObjectSlotArray[i].ViewMatrix = &gameData->RenderSlotArray[i].ViewMatrix;

        engineVariables->RenderObjectSlotArray[i].DepthTest = gameData->RenderSlotArray[i].DepthTest;

        engineVariables->RenderObjectSlotArray[i]._2D = gameData->RenderSlotArray[i]._2D;

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

        engineVariables->RenderObjectSlotArray[i].uniforms.Vec3 = &gameData->RenderSlotArray[i].uniforms.Vec3;
        engineVariables->RenderObjectSlotArray[i].uniforms.Float = &gameData->RenderSlotArray[i].uniforms.Float;
        ///---END Uniform assignment from game data ---///


    }

}

void HandleUniformNameError(const char* UniformName, const char* ShaderFile, unsigned int SlotNumber)
{
    std::cout << "\nRenderGU requires a shader uniform named \"" << UniformName << "\"" << std::endl;
    std::cout << "See shader " << ShaderFile << std::endl;
    std::cout << "RenderGU is currently processing render slot " << SlotNumber << " during tick\n" << std::endl;

}

void SetTransformMatrixUniforms(unsigned int ShaderProgram,
                                       glm::mat4& ModelMatrix,
                                       glm::mat4& ViewMatrix,
                                       glm::mat4& ProjectionMatrix,
                                       const char* ModelMatUniformName,
                                       const char* ViewMatUniformName,
                                       const char* ProjMatUniformName,
                                       std::vector<std::vector<bool>>& SlotErrorReported,
                                       unsigned int SlotNumber,
                                       struct GameData* gameData)
{
    // Model Matrix Uniform
    GLint LocModelMatUniform = glGetUniformLocation(ShaderProgram, ModelMatUniformName);
    if (LocModelMatUniform != -1)
    {
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, ModelMatUniformName), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
    }
    else if (!SlotErrorReported[SlotNumber][0])
    {
        SlotErrorReported[SlotNumber][0] = true;
        HandleUniformNameError(ModelMatUniformName, gameData->RenderSlotArray[SlotNumber].VertexShader, SlotNumber);
    }

    // View Matrix Uniform
    GLint LocViewMatUniform = glGetUniformLocation(ShaderProgram, ViewMatUniformName);
    if (LocViewMatUniform != -1)
    {
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, ViewMatUniformName), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
    }
    else if (!SlotErrorReported[SlotNumber][1])
    {
        SlotErrorReported[SlotNumber][1] = true;
        HandleUniformNameError(ViewMatUniformName, gameData->RenderSlotArray[SlotNumber].VertexShader, SlotNumber);
    }

    // Projection Matrix Uniform
    GLint LocProjMatUniform = glGetUniformLocation(ShaderProgram, ProjMatUniformName);
    if (LocProjMatUniform != -1)
    {
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, ProjMatUniformName), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
    }
    else if (!SlotErrorReported[SlotNumber][2])
    {
        SlotErrorReported[SlotNumber][2] = true;
        HandleUniformNameError(ProjMatUniformName, gameData->RenderSlotArray[SlotNumber].VertexShader, SlotNumber);
    }

}

void SetTransformMatrixUniforms_Instancing(unsigned int ShaderProgram,
                                glm::mat4& ViewMatrix,
                                glm::mat4& ProjectionMatrix,
                                const char* ViewMatUniformName,
                                const char* ProjMatUniformName,
                                std::vector<std::vector<bool>>& SlotErrorReported,
                                unsigned int SlotNumber,
                                struct GameData* gameData)
{

    // View Matrix Uniform
    GLint LocViewMatUniform = glGetUniformLocation(ShaderProgram, ViewMatUniformName);
    if (LocViewMatUniform != -1)
    {
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, ViewMatUniformName), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
    }
    else if (!SlotErrorReported[SlotNumber][1])
    {
        SlotErrorReported[SlotNumber][1] = true;
        HandleUniformNameError(ViewMatUniformName, gameData->RenderSlotArray[SlotNumber].VertexShader, SlotNumber);
    }

    // Projection Matrix Uniform
    GLint LocProjMatUniform = glGetUniformLocation(ShaderProgram, ProjMatUniformName);
    if (LocProjMatUniform != -1)
    {
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, ProjMatUniformName), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
    }
    else if (!SlotErrorReported[SlotNumber][2])
    {
        SlotErrorReported[SlotNumber][2] = true;
        HandleUniformNameError(ProjMatUniformName, gameData->RenderSlotArray[SlotNumber].VertexShader, SlotNumber);
    }

}
