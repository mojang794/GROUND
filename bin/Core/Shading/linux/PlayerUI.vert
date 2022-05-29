#version 120
attribute vec3 aPos;
attribute vec3 aColor;
attribute vec2 aTexcoord;

varying vec3 vPos, vColor;
varying vec2 vTexcoord;

uniform mat4 model;

void main()
{
    vPos = aPos;
    vColor = aColor;
    vTexcoord = aTexcoord;
    gl_Position = model * vec4(aPos, 1.0);
}