#version 460

layout (location = 20) out vec4 FragColor;

layout(location = 40) uniform vec3 LightColor;
layout(location = 41) uniform vec3 ObjectColor;
layout(location = 42) uniform float AmbientLightStrength;

void main()
{
    FragColor = vec4(AmbientLightStrength * LightColor * ObjectColor, 1.0f);
}
