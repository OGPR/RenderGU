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
        glm::mat4* ModelMatrix;
        glm::mat4* ViewMatrix;
        glm::mat4* ProjectionMatrix;
        
    };

    // TODO un-hardcode the size of this array.
    RenderObjectSlot RenderObjectSlotArray[3];


    unsigned int frameNumber = 0;
    bool pause = false;
    bool space_pressed = false;
};
