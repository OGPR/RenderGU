#version 460

layout (location = 20) out vec4 FragColor;
layout (location = 10)in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
    FragColor = texture(Texture, TexCoord);
}
