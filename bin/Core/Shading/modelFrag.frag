#version 330 core

out vec4 FragColor;

in vec3 vNormal;
in vec3 FragPos;
in float x, y, z;
in vec2 vUV;

uniform sampler2D uTexture1;
uniform vec3 lightColor, lightPos, viewPos;

vec3 DrawPointLight(
            vec3 vNormal, vec3 lightPos, vec3 lightColor, vec3 viewPos, vec3 FragPos, 
            float ambientStrength, float specularStrength, float impactValue);

void main()
{
    vec3 texturePixel = texture(uTexture1, vUV).rgb;
    if (length(texturePixel) == 0)
        FragColor = vec4(vUV, 1.0, 1.0) * vec4(DrawPointLight(vNormal, lightPos, lightColor, viewPos, FragPos, 0.1, 0.5, 32), 1.0);
    else
        FragColor = vec4(texturePixel, 1.0) * vec4(DrawPointLight(vNormal, lightPos, lightColor, viewPos, FragPos, 0.1, 0.5, 32), 1.0);
}