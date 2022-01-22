#pragma once
#include <glad/glad.h> // For OpenGL
#include <iostream>

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

unsigned int compileGeomShader(const char* geomShaderSource)
{
    unsigned int geomShader;
    geomShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geomShader, 1, &geomShaderSource, NULL);
    glCompileShader(geomShader);

    //geomShader compilation error checking
    {
        int success;
        char infoLog[512];
        glGetShaderiv(geomShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(geomShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }

    return geomShader;
}
