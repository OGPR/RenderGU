#pragma once

struct EngineVariables
{
    struct RenderObjectSlot
    {
        unsigned int VAO = 0;
        unsigned int EBO = 0;
        unsigned int ShaderProgram = 0;
        unsigned int Indices = 0;
        unsigned int* IndexArray = nullptr;
        unsigned int TextureID = 0;
        unsigned int TextureUnit = 0;
        glm::mat4* ModelMatrix = nullptr;
        glm::mat4* ViewMatrix = nullptr;
        glm::mat4* ProjectionMatrix = nullptr;

    };

    unsigned int NumberOfSlots;
    RenderObjectSlot* RenderObjectSlotArray = nullptr; 


    unsigned int frameNumber = 0;
    bool pause = false;
    bool space_pressed = false;

    bool Multithreaded = false;
};
