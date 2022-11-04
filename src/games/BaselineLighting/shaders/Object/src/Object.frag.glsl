#version 460

layout(location = 10) in vec3 Normal;
layout(location = 20) in vec3 VertexPosWS;
layout (location = 30) out vec4 FragColor;

layout(location = 40) uniform vec3 LightColor;
layout(location = 41) uniform vec3 ObjectColor;
layout(location = 42) uniform float AmbientLightStrength;
layout(location = 43) uniform vec3 LightPosition;

void main()
{
    vec3 FragmentToLightDir = normalize(LightPosition - VertexPosWS);
    vec3 UnitVertexNormal = normalize(Normal);

    float DiffuseComponent = max(dot(UnitVertexNormal, LightPosition), 0.0f);

    FragColor = vec4((DiffuseComponent + AmbientLightStrength) * LightColor * ObjectColor, 1.0f);
}
