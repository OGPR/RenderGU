#pragma once

struct TriangleSceneData
{
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    float fadeAmount = 0.0f;
};

void displayTriangle(unsigned int* VAO, unsigned int* shaderProgram, float* fadeAmount)
{

    if (!*VAO) // Create model, specify vertices and compile shaders in only once in the loop that this function will be called in
    {
        float vertexDataArr[15] = {0};
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

        //Tex coords
        *vertexData++ = 1.0f; 
        *vertexData++ = 0.0f; 

        *vertexData++ = 0.0f; 
        *vertexData++ = 1.0f; 

        *vertexData++ = 0.0f; 
        *vertexData++ = 0.0f; 
        
            
        // Write shaders
        const char* vs =
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 texCoord;

            out vec2 aTexCoord;

            void main()
            {
                gl_Position = vec4(inPos, 1.0f);
                aTexCoord = texCoord;
            }
            );
        const char* fs =
            GLSL(330 core,
            in vec2 aTexCoord;
            out vec4 FragColor;

            uniform sampler2D Texture;

            void main()
            {
                vec4 texColor = texture(Texture, aTexCoord);
                FragColor = texColor;
            }
            );


        // Make Shader Program
        *shaderProgram = linkShaders(compileVertexShader(vs),
                compileFragmentShader(fs));


       
        
        // Specify Vertices
        BindVBO(CreateVBO());
        AllocateMemoryVBO(15, vertexDataArr);
        *VAO = CreateVAO();
        assert(*VAO);
        BindVAO(*VAO);
        SetAttribute(0, 3, 0, (void*)0);
        SetAttribute(1, 2, 0, (void*)(9 * sizeof(float)));

    } // !VAO

    glClear(GL_COLOR_BUFFER_BIT);

    ////--- START Compute shader stuff ---////
    
    // Texture info for compute shader 
    GLuint texOut;
    int texWidth = 512;
    int texHeight = 512;

    // Texture creation 
    glGenTextures(1, &texOut);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texOut);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, texWidth, texHeight, 0, GL_RGBA, GL_FLOAT, nullptr);
    glBindImageTexture(0, texOut, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    const char* cs =
        GLSL(430 core,
        layout(local_size_x = 1, local_size_y = 1) in;
        layout(rgba32f, binding = 0) uniform image2D img_output;

        uniform float fadeAmount;

        void main()
        {
            vec4 pixel = vec4(0.12f + fadeAmount, 0.939f - fadeAmount, 0.684f, 1.0f);
            ivec2 pixel_coords = ivec2(gl_GlobalInvocationID.xy);
            imageStore(img_output, pixel_coords, pixel);
        }
        );

    unsigned int computeShaderProgram = linkShaders(compileComputeShader(cs));


    glUseProgram(computeShaderProgram);

    glUniform1f(glGetUniformLocation(computeShaderProgram, "fadeAmount"), *fadeAmount); 

    glDispatchCompute((GLuint)texWidth, (GLuint)texHeight, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    ////--- END Compute shader stuff ---////


    glUseProgram(*shaderProgram);
    glBindVertexArray(*VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


