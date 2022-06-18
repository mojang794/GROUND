#version 330 core

in vec2 vUV;

uniform sampler2D uTexture1;

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.5686, 0.0, 1.0);
}