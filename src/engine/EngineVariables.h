#pragma once

struct EngineVariables
{
    struct RenderObjectSlot
    {
        unsigned int VAO = 0;
        unsigned int ShaderProgram = 0;
        unsigned int Indices = 0;
        unsigned int TextureID = 0;
        unsigned int TextureUnit = 0;
        glm::mat4* ModelMatrix = nullptr;
        glm::mat4* ViewMatrix = nullptr;
        glm::mat4* ProjectionMatrix = nullptr;

        bool IndexedDraw = false;

        bool DepthTest = false;

		struct Uniforms
		{
            struct _Vec3
            {
                const char* Name = nullptr;
                glm::vec3 Value;

            }Vec3;

		}uniforms;
    };

    unsigned int NumberOfSlots;
    RenderObjectSlot* RenderObjectSlotArray = nullptr; 


    unsigned int frameNumber = 0;
    bool pause = false;
    bool space_pressed = false;

    bool GLSLCompile = false;

};
