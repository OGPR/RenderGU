#pragma once

#include "../Utility.h"
#include "EngineModelDataInterface.h" 

#ifndef GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif
#include <utility>
#include <vector>

struct RenderSlot
{
    ModelData Model;

    unsigned int NumAttributes = 0;

    const char* VertexShader = nullptr;
    const char* FragmentShader = nullptr;
    const char* Texture = nullptr;
    unsigned int TextureArrayIndex = 0;

    glm::mat4 ModelMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ProjectionMatrix; 

    bool Draw = false; 

    bool DepthTest = false;

    struct Uniforms
    {
		std::vector<std::pair<const char*, glm::vec3>> Vec3;
		std::vector<std::pair<const char*, float>> Float;

    }uniforms;
};

