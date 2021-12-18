#pragma once

//macro to write shader programs inline
#ifndef GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif

const char* vertexShaderTriangle =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec3 aColour;
    out vec3 Colour;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        Colour = aColour;
    }
);

const char* fragmentShaderTriangle =
    GLSL(330 core,
    out vec4 FragColor;
	in vec3 Colour;

    void main()
    {
        FragColor = vec4(Colour, 1.0f);
    }
);
