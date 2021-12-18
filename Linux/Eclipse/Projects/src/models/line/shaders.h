#pragma once

//macro to write shader programs inline
#ifndef GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif

const char* vertexShaderLine =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
    }
);

const char* fragmentShaderLine =
    GLSL(330 core,
    out vec4 FragColor;

    uniform vec3 color;

    void main()
    {
        FragColor = vec4(color, 1.0f);
    }
);