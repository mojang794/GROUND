#version 120

varying vec3 vNormal;
varying vec3 FragPos;
varying float x, y, z;
varying vec2 vUV;

uniform sampler2D uTexture1;
uniform vec3 lightColor, lightPos, viewPos;

vec3 DrawPointLight(
            vec3 vNormal, vec3 lightPos, vec3 lightColor, vec3 viewPos, vec3 FragPos, 
            float ambientStrength, float specularStrength, float impactValue);

void main()
{
    vec3 texturePixel = texture2D(uTexture1, vUV).rgb;
    gl_FragColor = vec4(texturePixel, 1.0) * vec4(DrawPointLight(vNormal, lightPos, lightColor, viewPos, FragPos, 0.1, 0.5, 32), 1.0);
}