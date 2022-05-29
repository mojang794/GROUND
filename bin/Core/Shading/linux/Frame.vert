#version 120
attribute vec3 aPos;
attribute vec2 aTexcoord;

varying vec2 vTexcoords;
uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos, 1.0);
    vTexcoords = aTexcoord;
}