#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform vec4 objectColor;
uniform sampler2D textureSample;

void main()
{
    FragColor = texture(textureSample, texCoord) * objectColor;
}