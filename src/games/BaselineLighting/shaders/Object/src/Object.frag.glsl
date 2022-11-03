#version 460

layout (location = 20) out vec4 FragColor;

layout(location = 40) uniform vec3 LightColor;

void main()
{
    FragColor = vec4(LightColor, 1.0f) * vec4(0.0f, 0.0f, 1.0f, 1.f);
}
