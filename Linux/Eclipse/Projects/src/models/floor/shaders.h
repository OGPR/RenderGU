#pragma once

//macro to write shader programs inline
#ifndef GLSL
#define GLSL(version,A) "#version " #version "\n" #A
#endif

const char* vertexShaderFloor =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec2 aTexCoords;

	out vec2 TexCoords;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        TexCoords = aTexCoords;
    }
);

const char* fragmentShaderFloor =
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
            FragColor = texture(Texture, TexCoords);
        }
        else
        {
            //FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
            float depth = LineariseDepth(gl_FragCoord.z)/far*3;
            FragColor = vec4(vec3(depth), 1.f);
        }

    }
);
