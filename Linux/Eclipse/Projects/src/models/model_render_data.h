#pragma once

#include <vector>

struct ModelRenderData
{
    unsigned int VAO;
    unsigned int ShaderProgram;

    ModelRenderData(const char* vertexShader, const char* fragmentShader)
    : VertexShader(vertexShader), FragmentShader(fragmentShader)
    {}

    const char* VertexShader;
    const char* FragmentShader;
};

ModelRenderData floorRenderData(vertexShaderFloor, fragmentShaderFloor);

std::vector<ModelRenderData*> modelRenderDataList
{
    &floorRenderData
};
