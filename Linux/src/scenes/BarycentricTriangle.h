#pragma once

struct TriangleSceneData
{
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
};

void displayTriangle(unsigned int* VAO, unsigned int* shaderProgram)
{
    if (!*VAO) // Create model, specify vertices and compile shaders in only once in the loop that this function will be called in
    {
        float vertexDataArr[18] = {0};
        float* vertexData = vertexDataArr;
        
        // Tri 1
        
        // Row 1 (bottom left)
        *vertexData++ = -0.5f; // x
        *vertexData++ = -0.5f; // y
        *vertexData++ = 0.0f; // z

        // Row 2 (top center)
        *vertexData++ = 0.0f; // x
        *vertexData++ = 0.5f; // y
        *vertexData++ = 0.0f; // z

        // Row 3 (bottom right)
        *vertexData++ = 0.5f; // x
        *vertexData++ = -0.5f; // y
        *vertexData++ = 0.0f; // z

        //Colors
        *vertexData++ = 1.0f; 
        *vertexData++ = 0.0f; 
        *vertexData++ = 0.0f; 

        *vertexData++ = 0.0f; 
        *vertexData++ = 1.0f; 
        *vertexData++ = 0.0f; 

        *vertexData++ = 0.0f; 
        *vertexData++ = 0.0f; 
        *vertexData++ = 1.0f; 
        
            
        // Write shaders
        const char* vs =
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec3 inColor;

            out vec3 Color;

            void main()
            {
                gl_Position = vec4(inPos, 1.0f);
                Color = inColor;
            }
            );
        const char* fs =
            GLSL(330 core,
            in vec3 Color;
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(Color, 1.0f);
            }
            );

        // Make Shader Program
        *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

        // Specify Vertices
        BindVBO(CreateVBO());
        AllocateMemoryVBO(18, vertexDataArr);
        *VAO = CreateVAO();
        assert(*VAO);
        BindVAO(*VAO);
        SetAttribute(0, 3, 0, (void*)0);
        SetAttribute(1, 3, 0, (void*)(9 * sizeof(float)));

    } // !VAO

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


