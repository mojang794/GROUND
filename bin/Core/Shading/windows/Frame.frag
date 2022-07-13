#version 330 core

uniform sampler2D uTexture;
uniform float _clock;
in vec2 vTexcoords;
out vec4 FragColor;

vec3 StaticTVNoise(vec2 texcoords, float _clock);
vec4 TVScreenEffect(vec2 texcoords, sampler2D texture);

void main()
{
    FragColor = texture(uTexture, vTexcoords);//TVScreenEffect(vTexcoords, uTexture) * vec4(StaticTVNoise(vTexcoords, _clock), 0.0);
}