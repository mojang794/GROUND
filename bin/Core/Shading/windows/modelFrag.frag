#version 330 core

out vec4 FragColor;

in vec3 vNormal;
in vec3 FragPos;
in vec2 vUV;

uniform sampler2D uTexture1;
uniform vec3 lightColor, lightPos, viewPos, viewFront;

vec3 DrawPointLight(
            vec3 vNormal, vec3 lightPos, vec3 lightColor, vec3 viewPos, vec3 FragPos, 
            float ambientStrength, float specularStrength, float impactValue);

vec3 DrawSpotLight(
    vec3 vNormal, vec3 lightColor, vec3 viewPos, vec3 FragPos, vec3 Lposition, vec3 direction, 
    float ambientStrength, float specularStrength, float impactValue);

void main()
{
    vec3 texturePixel = texture(uTexture1, vUV).rgb;
    FragColor = vec4(texturePixel, 1.0);
}