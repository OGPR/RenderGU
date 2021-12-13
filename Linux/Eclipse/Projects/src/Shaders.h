#pragma once

//macro to write shader programs inline
#ifndef GLSL 
#define GLSL(version,A) "#version " #version "\n" #A
#endif







//// Transparency rectangle shaders
const char* vertexShaderSource_Rect_Transparency =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec2 aTexCoord;

    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        TexCoord = aTexCoord;
    }
);

const char* fragmentShaderSource_Rect_Transparency =
    GLSL(330 core,
	in vec2 TexCoord;
	in vec3 Color;
    out vec4 FragColor;

    uniform sampler2D Texture;


    void main()
    {
    	vec4 texColor = texture(Texture, TexCoord);
    	if (texColor.a < 0.1)
    		discard;
    	FragColor = texColor;
    }
);

// Window
// re-using VShader from rect_transp
const char* fragmentShaderSource_Rect_window =
    GLSL(330 core,
	in vec2 TexCoord;
	in vec3 Color;
    out vec4 FragColor;

    uniform sampler2D Texture;


    void main()
    {
    	FragColor = texture(Texture, TexCoord);
    }
);





