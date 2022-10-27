#version 460

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inTexCoord;

layout (location = 10) out vec2 TexCoord;

layout(location = 100) uniform mat4 ModelMatrix;
layout(location = 101) uniform mat4 ViewMatrix;
layout(location = 102) uniform mat4 ProjectionMatrix;

void main()
{
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inPos, 1.0f);
    TexCoord = inTexCoord;

}
