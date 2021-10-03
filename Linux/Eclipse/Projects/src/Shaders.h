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
    layout(location = 1) in vec3 aColour;
    layout(location = 2) in vec2 aTexCoord;
    out vec3 Colour;
    out vec2 TexCoord;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        Colour = aColour;
        TexCoord = aTexCoord;
    }
);

const char* fragmentShaderSource_Tri =
    GLSL(330 core,
    out vec4 FragColor;
	in vec3 Colour;
	in vec2 TexCoord;

	uniform sampler2D Texture;

    void main()
    {
        //FragColor = vec4(Colour, 1.0f);
        FragColor = texture(Texture, TexCoord);
    }
);

//// Rectangle data shaders
const char* vertexShaderSource_Rect =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec3 aColour;
    layout(location = 2) in vec2 aTexCoord;
    out vec3 Colour;
    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        Colour = aColour;
        TexCoord = aTexCoord;
    }
);

const char* fragmentShaderSource_Rect =
    GLSL(330 core,
    out vec4 FragColor;
	in vec3 Colour;
	in vec2 TexCoord;

	uniform sampler2D Texture1;
	uniform sampler2D Texture2;
	uniform bool vertFlip = false;
	uniform float texture2Amount = 0.2f;

    void main()
    {
        //FragColor = vec4(Colour, 1.0f);
    	if (vertFlip)
			FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), texture2Amount);
    	else
			FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, TexCoord), texture2Amount);
    }
);

//// cube data shaders
const char* vertexShaderSource_Cube =
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

const char* fragmentShaderSource_Cube =
    GLSL(330 core,
    out vec4 FragColor;
	in vec2 TexCoord;

	uniform sampler2D Texture1;
	uniform sampler2D Texture2;
	uniform bool vertFlip = false;
	uniform float texture2Amount = 0.2f;

    void main()
    {
        //FragColor = vec4(Colour, 1.0f);
    	if (vertFlip)
			FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), texture2Amount);
    	else
			FragColor = mix(texture(Texture1, TexCoord), texture(Texture2, TexCoord), texture2Amount);
    }
);

const char* vertexShaderSource_Cube_Raw_Target =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
);

const char* fragmentShaderSource_Cube_Raw_Target =
    GLSL(330 core,
    out vec4 FragColor;

	uniform vec3 reflectance;
	uniform vec3 lightSource;

    void main()
    {
    	FragColor = vec4(reflectance * lightSource, 1.0f);
    }
);

const char* vertexShaderSource_Cube_Raw_LightSource =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
);

const char* fragmentShaderSource_Cube_Raw_LightSource =
    GLSL(330 core,
    out vec4 FragColor;

	uniform vec3 lightSource;

    void main()
    {
    	FragColor = vec4(lightSource, 1.0f);
    }
);
