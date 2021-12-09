#pragma once

//macro to write shader programs inline
#ifndef GLSL 
#define GLSL(version,A) "#version " #version "\n" #A
#endif



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



const char* fragmentShaderSource_Cube_no_mix =
    GLSL(330 core,
    out vec4 FragColor;
	in vec2 TexCoord;

	uniform sampler2D Texture;
	uniform bool visualiseDepthBuffer;

	float near = 0.1f;
	float far = 100.f;
	float LineariseDepth(float depth)
	{
		float z = depth * 2.f - 1.f;
		return (2.f * near * far)/(far + near - z * (far - near));
	}

    void main()
    {
    	if (!visualiseDepthBuffer)
    	{
    		FragColor = texture(Texture, TexCoord);
    	}
    	else
    	{
			//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
			float depth = LineariseDepth(gl_FragCoord.z)/far*3;
			FragColor = vec4(vec3(depth), 1.f);
    	}
    }
);






const char* fragmentShaderSingleColor =
    GLSL(330 core,
    in vec2 TexCoords;
    out vec4 FragColor;

    uniform sampler2D Texture;
    uniform bool visualiseDepthBuffer;

	float near = 0.1f;
	float far = 100.f;
	float LineariseDepth(float depth)
	{
		float z = depth * 2.f - 1.f;
		return (2.f * near * far)/(far + near - z * (far - near));
	}
    void main()
    {
    	if (!visualiseDepthBuffer)
    	{
			FragColor = vec4(0.04f, 0.28f, 0.26f, 1.f);
    	}
    	else
    	{
			//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
			FragColor = vec4(0.04f, 0.28f, 0.26f, 1.f);
    	}

    }
);

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





