//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================


#include "CompileShaders.h"
#include "LinkShaders.h"
#include "Window.h"
#include "models/floor/model.h"
#include "models/floor/vertex_specification.h"
#include "models/floor/shaders.h"
#include "Rendering_Common.h"
#include "models/model_render_data.h"
#include "scenes/CubeGrassWindowFloor/render.h"


// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}

void RenderSetup(std::vector<ModelRenderData*> * modelRenderDataList)
{
    if (modelRenderDataList)
    {
        for (ModelRenderData* modelRenderData : *modelRenderDataList)
        {
            modelRenderData->ShaderProgram = linkShaders(
                    compileVertexShader(modelRenderData->VertexShader),
                    compileFragmentShader(modelRenderData->FragmentShader)
                    );

            modelRenderData->VAO = vertex_specification_floor(floor_model, 18 + 12);
        }
    }
}

int main()
{
    GLFWwindow* window = Window();

    RenderSetup(&modelRenderDataList);

    SceneRender_CubeGrassWindowFloor(window);

    Terminate();
    return 0;





}
