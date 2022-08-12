#pragma once

struct EngineVariables
{
    // VAOs and ShaderPrograms
    unsigned int shaderProgram = 0;
    unsigned int VAO = 0;

    unsigned int frameNumber = 0;
    bool pause = false;
    bool space_pressed = false;
};
