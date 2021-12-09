#pragma once

#pragma once

//macro to write shader programs inline
#ifndef GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif

//// Simple quad render shaders
const char* vertexShaderSimpleCube =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;

    out vec3 TexCoord;

    uniform mat4 model;
    uniform mat4 projection;
    uniform mat4 view;

    void main()
    {
    	gl_Position =  projection * view * model * vec4(aPos , 1.0);
        TexCoord = aPos;
    }
);

const char* fragmentShaderSimpleCube =
    GLSL(330 core,
	in vec3 TexCoord;
    out vec4 FragColor;

    uniform samplerCube Texture;

    void main()
    {
        FragColor = texture(Texture, TexCoord);
    }
);