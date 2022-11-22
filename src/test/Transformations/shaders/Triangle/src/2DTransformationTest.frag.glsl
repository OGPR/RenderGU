#version 460

layout(location = 20) out vec4 FragColor;

layout(location = 200) uniform vec3 Color;

void main()
{
    FragColor = vec4(Color, 1.0f);
}
