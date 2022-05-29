#version 120

uniform vec3 ObjectColor;

void main()
{
    gl_FragColor = vec4(ObjectColor, 1.0);
}