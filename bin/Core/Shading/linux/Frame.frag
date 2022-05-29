#version 120

uniform sampler2D uTexture;
varying vec2 vTexcoords;

void main()
{
    vec2 p = vTexcoords.st;
    p.x -= mod(p.x, 1.0 / 200);
    p.y -= mod(p.y, 1.0 / 200);

    gl_FragColor = texture2D(uTexture, p);
}