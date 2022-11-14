#version 460

layout (location = 20) out vec4 FragColor;

layout(location = 30) uniform vec3 LightColor;


void main()
{
    FragColor = vec4(LightColor, 0.f);
}
