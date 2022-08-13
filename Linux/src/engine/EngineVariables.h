#pragma once

struct EngineVariables
{
    struct RenderObjectSlot1
    {
        unsigned int VAO = 0;
        unsigned int ShaderProgram = 0;
        unsigned int Indices = 0;
        glm::mat4 ModelMatrix = glm::mat4(1.0f);
        glm::mat4 ViewMatrix = glm::mat4(1.0f);
        glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
        
    } renderObjectSlot1;


    unsigned int frameNumber = 0;
    bool pause = false;
    bool space_pressed = false;
};
