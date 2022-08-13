#pragma once

struct EngineVariables
{
    struct RenderObjectSlot1
    {
        unsigned int VAO = 0;
        unsigned int ShaderProgram = 0;
    } renderObjectSlot1;


    unsigned int frameNumber = 0;
    bool pause = false;
    bool space_pressed = false;
};
