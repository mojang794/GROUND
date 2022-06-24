#version 330 core

out vec4 FragColor;

in vec3 vColor;
in vec2 vTexcoord;
in vec3 vNormal;
in vec3 vPos;
in vec3 FragPos;

uniform vec3 lightColor, lightPos, viewPos, viewFront;

vec3 DrawPointLight(vec3 vNormal, vec3 lightPos, vec3 lightColor, vec3 viewPos, vec3 FragPos, float ambientStrength, float specularStrength, float impactValue);

void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, 0.2);
}