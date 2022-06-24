#version 330 core

uniform sampler2D uTexture;
in vec2 vTexcoords;
out vec4 FragColor;

void main()
{
    vec2 p = vTexcoords.st;
    p.x -= mod(p.x, 1.0 / 128);
    p.y -= mod(p.y, 1.0 / 128);

    FragColor = texture(uTexture, p);
}