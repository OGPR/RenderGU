#version 460

layout(location = 0) in vec3 inPos;

layout(location = 100) uniform mat4 ViewMatrix;
layout(location = 101) uniform mat4 ProjectionMatrix;
layout(location = 102) uniform mat4 ModelMatrix;

void main()
{
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inPos, 1.0f);
}
