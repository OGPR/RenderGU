#pragma once

//macro to write shader programs inline
#ifndef GLSL 
#define GLSL(version,A) "#version " #version "\n" #A
#endif

const char* vertexShaderSource =
    GLSL(330 core,
    uniform float R_ChannelValue;
    uniform float G_ChannelValue;
    uniform float B_ChannelValue;
    layout(location = 0) in vec3 aPos;
    out vec3 vColor;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        vColor = vec3(0.f + R_ChannelValue, 0.f + G_ChannelValue, 0.f + B_ChannelValue);
    }
);

const char* fragmentShaderSource =
    GLSL(330 core,
    out vec4 FragColor;
    in vec3 vColor;

    void main()
    {
        FragColor = vec4(vColor, 1.0f);
    }
);

//// Triangle data shaders
const char* vertexShaderSource_Tri =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
);

const char* fragmentShaderSource_Tri =
    GLSL(330 core,
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.f, 0.f, 1.0f, 1.0f);
    }
);

