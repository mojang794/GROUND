#version 330 core

out vec4 FragColor;

in vec3 textureCoord;

uniform samplerCube skybox;

void main()
{
    FragColor = vec4(texture(skybox, textureCoord).rgb, 1.0);
}