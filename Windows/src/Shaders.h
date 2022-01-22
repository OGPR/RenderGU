#pragma once

//macro to write shader programs inline
#ifndef GLSL 
#define GLSL(version,A) "#version " #version "\n" #A
#endif

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

    void main()
    {
        FragColor = vec4(Colour, 1.0f);
    }
);

//// Point data shaders
const char* vertexShaderSource_Point =
    GLSL(330 core,
    layout(location = 0) in vec3 aPos;

    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
);

const char* geomShaderSource_Point =
    GLSL(330 core,
    layout(points) in;
	layout(line_strip, max_vertices = 2) out;

    void main()
    {

        gl_Position = gl_in[0].gl_Position + vec4(0.5f, vec2(0.0f), 1.0f);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(-0.5f, vec2(0.0f), 1.0f);
        EmitVertex();

        EndPrimitive();
    }
);

const char* fragmentShaderSource_Point =
    GLSL(330 core,
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(0.4f, 0.9f, 0.2f, 1.0f);
    }
);
