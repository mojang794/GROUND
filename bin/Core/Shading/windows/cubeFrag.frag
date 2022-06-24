#version 330 core

out vec4 FragColor;

in vec3 vColor;
in vec2 vTexcoord;
in vec3 vNormal;
in vec3 FragPos;

uniform sampler2D uTexture;
uniform vec3 lightColor, lightPos, viewPos, viewFront;

vec3 DrawPointLight(vec3 vNormal, vec3 lightPos, vec3 lightColor, vec3 viewPos, vec3 FragPos, float ambientStrength, float specularStrength, float impactValue);

void main()
{
    vec3 Tpixel = texture(uTexture, vTexcoord).rgb;

    if (length(Tpixel) == 0)
        FragColor = vec4(DrawPointLight(vNormal, lightPos, lightColor, viewPos, FragPos, 0.1, 0.5, 32), 1.0) * vec4(Tpixel, 1.0);
    else
        FragColor = vec4(DrawPointLight(vNormal, lightPos, lightColor, viewPos, FragPos, 0.1, 0.5, 32), 1.0) * vec4(1.0, 0.0, 0.949, 1.0);
}