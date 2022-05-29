#version 120
attribute vec3 aPos;
attribute vec3 aColor;
attribute vec2 aTexcoord;
attribute vec3 aNormal;
attribute vec2 aUV;

varying vec2 vTexcoord;
varying vec3 vColor;
varying vec3 vNormal;
varying vec2 vUV;
varying vec3 FragPos;

uniform mat4 projection, model, view;

void main()
{
    vTexcoord = aTexcoord;
    vColor = aColor;

    vNormal = aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    vUV = aUV;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}