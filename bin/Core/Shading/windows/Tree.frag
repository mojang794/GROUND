#version 330 core

in vec3 vLightColor, vViewPos, vLightPos, vViewFront;
in vec3 FragPos;
in vec2 vTexcoord;
in vec3 vNormal;

out vec4 FragColor;
uniform sampler2D uTexture;

vec3 DrawPointLight(vec3 vNormal, vec3 lightPos, vec3 lightColor, vec3 viewPos, vec3 FragPos, float ambientStrength, float specularStrength, float impactValue);

void main()
{
    FragColor = texture(uTexture, vTexcoord) * vec4(DrawPointLight(vNormal, vLightPos, vLightColor, vViewPos, FragPos, 1.0, 0.32, 32.0), 1.0);
}