#version 120

varying vec3 vColor;
varying vec2 vTexcoord;
varying vec3 vNormal;
varying vec3 FragPos;

uniform sampler2D uTexture;
uniform vec3 lightColor, lightPos, viewPos, viewFront;

vec3 DrawPointLight(vec3 vNormal, vec3 lightPos, vec3 lightColor, vec3 viewPos, vec3 FragPos, float ambientStrength, float specularStrength, float impactValue);

void main()
{
    vec3 Tpixel = texture2D(uTexture, vTexcoord).rgb;

    gl_FragColor = vec4(DrawPointLight(vNormal, lightPos, lightColor, viewPos, FragPos, 0.1, 0.5, 32), 1.0) * vec4(vTexcoord, 1.0, 1.0);
}