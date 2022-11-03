#version 460

layout (location = 20) out vec4 FragColor;

layout(location = 40) uniform vec3 LightColor;
layout(location = 41) uniform vec3 ObjectColor;

void main()
{
    FragColor = vec4(LightColor * ObjectColor, 1.0f);
}
