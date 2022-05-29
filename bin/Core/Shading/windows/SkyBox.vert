#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 projection, view, model;

out vec3 textureCoord;

void main()
{
    textureCoord = aPos;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}