#version 330 core

out vec4 FragColor;
in vec3 vColor;

in vec3 vLightColor, vViewPos, vLightPos, vViewFront;
in vec3 FragPos;
in vec3 vNormal;

vec3 DrawPointLight(vec3 vNormal, vec3 lightPos, vec3 lightColor, vec3 viewPos, vec3 FragPos, float ambientStrength, float specularStrength, float impactValue);

void main()
{
    FragColor = vec4(vColor, 1.0) * vec4(DrawPointLight(vNormal, vLightPos, vLightColor, vViewPos, FragPos, 1, 0.32, 32), 1.0);
}