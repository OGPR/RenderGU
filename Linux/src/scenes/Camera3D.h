#pragma once
#include <glm/glm.hpp>

struct Camera3DSceneData
{
    unsigned int VAO = 0;
    unsigned int shaderProgram = 0;
    unsigned int texture = 0;
    float* model = nullptr;
    glm::mat4 modelMat = glm::mat4(1.0f);
    glm::mat4 viewMat = glm::mat4(1.0f);
    glm::mat4 projectionMat = glm::mat4(1.0f);
};

void displayCube(unsigned int* VAO,
        unsigned int* shaderProgram,
        unsigned int* texture,
        float* model,
        glm::mat4* modelMat,
        glm::mat4* viewMat,
        glm::mat4* projectionMat)
{
    assert(model);

    if (!*VAO) // Create model, specify vertices and compile shaders in only once in the loop that this function will be called in
    {
        float vertexDataArr[180] = {0};
        float* vertexData = vertexDataArr;
        
        unsigned char vertexDataCount = 0;
        while (vertexDataCount < 180)
        {
            ++vertexDataCount;
            *vertexData++ = *model++;
        }
            
        // Write shaders
        const char* vs =
            GLSL(330 core,
            layout(location = 0) in vec3 inPos;
            layout(location = 1) in vec2 inTexCoord;
            out vec2 TexCoord;

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            void main()
            {
                gl_Position = projection * view * model * vec4(inPos, 1.0f);
                TexCoord = inTexCoord;
            }
        );

        const char* fs =
            GLSL(330 core,
            out vec4 FragColor;
                in vec2 TexCoord;

                uniform sampler2D Texture;

                void main()
                {
                    // vec4 texColor = texture(Texture, texCoord);
                    FragColor = vec4(0.3f, 0.7f, 0.4f, 1.0f);
                }
        );

        // Make Shader Program
        *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

        // Specify Vertices
        BindVBO(CreateVBO());
        AllocateMemoryVBO(180, vertexDataArr);
        *VAO = CreateVAO();
        assert(*VAO);
        BindVAO(*VAO);
        SetAttribute(0, 3, 5 * sizeof(float), (void*)0);
        SetAttribute(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    } // !VAO


    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(*shaderProgram);
    glBindVertexArray(*VAO);

    glUniformMatrix4fv(glGetUniformLocation(*shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(*modelMat));
    glUniformMatrix4fv(glGetUniformLocation(*shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(*viewMat));
    glUniformMatrix4fv(glGetUniformLocation(*shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(*projectionMat));

    glDrawArrays(GL_TRIANGLES, 0, 36);
}


