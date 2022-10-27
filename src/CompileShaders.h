#pragma once
#include <glad/glad.h> // For OpenGL
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

unsigned int createVertexShader(const char* vertexShaderSPIRVBinary)
{
    unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Load shader binary into a vector
    std::ifstream InputStream(vertexShaderSPIRVBinary, std::ios::binary);
    std::istreambuf_iterator<char> StartIt(InputStream);
    std::istreambuf_iterator<char> EndIt;
    std::vector<char> Buffer(StartIt, EndIt);
    InputStream.close();

    glShaderBinary(1, &VertexShader, GL_SHADER_BINARY_FORMAT_SPIR_V, Buffer.data(), Buffer.size());
    glSpecializeShader(VertexShader, "main", 0, 0, 0);

    // Check for success
    GLint Status;
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Status);
    if (Status == GL_FALSE)
    {
        char cwd[PATH_MAX];
        if( !getcwd(cwd, sizeof(cwd)))
            printf("getcwd error!\n");

        printf("Loading %s failed!\n", vertexShaderSPIRVBinary);
        printf("We are looking in %s\n", cwd);
    }

    
    return VertexShader;
}

unsigned int createFragmentShader(const char* fragmentShaderSPIRVBinary)
{
    unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Load shader binary into a vector
    std::ifstream InputStream(fragmentShaderSPIRVBinary, std::ios::binary);
    std::istreambuf_iterator<char> StartIt(InputStream);
    std::istreambuf_iterator<char> EndIt;
    std::vector<char> Buffer(StartIt, EndIt);
    InputStream.close();

    glShaderBinary(1, &FragmentShader, GL_SHADER_BINARY_FORMAT_SPIR_V, Buffer.data(), Buffer.size());
    glSpecializeShader(FragmentShader, "main", 0, 0, 0);

    // Check for success
    GLint Status;
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Status);
    if (Status == GL_FALSE)
    {
        char cwd[PATH_MAX];
        if( !getcwd(cwd, sizeof(cwd)))
            printf("getcwd error!\n");

        printf("Loading %s failed!\n", fragmentShaderSPIRVBinary);
        printf("We are looking in %s\n", cwd);
    }
    
    return FragmentShader;
}

unsigned int compileVertexShader(const char* vertexShaderSource)
{
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //vertexShader compilation error checking
    {
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    return vertexShader;
}

unsigned int compileFragmentShader(const char* fragmentShaderSource)
{
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //fragmentShader compilation error checking
    {
        int success;
        char infoLog[512];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    return fragmentShader;
}

unsigned int compileComputeShader(const char* computeShaderSource)
{
    unsigned int computeShader;
    computeShader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(computeShader, 1, &computeShaderSource, NULL);
    glCompileShader(computeShader);

    //fragmentShader compilation error checking
    {
        int success;
        char infoLog[512];
        glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(computeShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPUTE::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    return computeShader;
}
