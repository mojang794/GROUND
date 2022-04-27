#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexcoord;

out vec3 vPos, vColor;
out vec2 vTexcoord;

uniform mat4 model;

void main()
{
    vPos = aPos;
    vColor = aColor;
    vTexcoord = aTexcoord;
    gl_Position = model * vec4(aPos, 1.0);
}