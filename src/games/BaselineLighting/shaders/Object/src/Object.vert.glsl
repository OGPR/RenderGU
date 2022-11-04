#version 460

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;

layout(location = 10) out vec3 Normal;
layout(location = 20) out vec3 VertexPosWS;


layout(location = 100) uniform mat4 ModelMatrix;
layout(location = 101) uniform mat4 ViewMatrix;
layout(location = 102) uniform mat4 ProjectionMatrix;

void main()
{
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(inPos, 1.0f);
    VertexPosWS = vec3(ModelMatrix * vec4(inPos, 1.0f));
    Normal = inNormal;
}
