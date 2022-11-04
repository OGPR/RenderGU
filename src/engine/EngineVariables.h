#pragma once

#include <utility>
#include <vector>

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
            std::vector<std::pair<const char*, glm::vec3>> Vec3;
            std::vector<std::pair<const char*, float>> Float;

		}uniforms;


    };

    unsigned int NumberOfSlots;
    RenderObjectSlot* RenderObjectSlotArray = nullptr; 


    unsigned int frameNumber = 0;
    bool pause = false;
    bool space_pressed = false;

    bool GLSLCompile = false;

};
