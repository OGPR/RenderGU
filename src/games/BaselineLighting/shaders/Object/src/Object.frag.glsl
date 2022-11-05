#version 460

layout(location = 10) in vec3 Normal;
layout(location = 20) in vec3 FragPos;
layout (location = 30) out vec4 FragColor;

layout(location = 40) uniform vec3 LightColor;
layout(location = 41) uniform vec3 ObjectColor;
layout(location = 42) uniform float AmbientLightStrength;
layout(location = 43) uniform vec3 LightPosition;
layout(location = 44) uniform vec3 EyePosition;

void main()
{
    vec3 FragmentToLightDir = normalize(LightPosition - FragPos);
    vec3 FragmentToEyeDir = normalize(EyePosition - FragPos);

    vec3 UnitFragmentNormal = normalize(Normal);

    vec3 FragmentToLightReflectDir = reflect(-FragmentToLightDir, UnitFragmentNormal);

    float DiffuseComponent = max(dot(UnitFragmentNormal, FragmentToLightDir), 0.0f);

    float SpecularComponent = pow(max(dot(FragmentToEyeDir, FragmentToLightReflectDir), 0.0f), 64);
    
    FragColor = vec4((DiffuseComponent + AmbientLightStrength + SpecularComponent * 0.5f) * LightColor * ObjectColor, 1.0f);

    // TODO - explore these visualisation
    //FragColor = vec4(VertexPosWS, 1.0f);
    //FragColor = vec4(FragmentToLightDir, 1.0f);
}
