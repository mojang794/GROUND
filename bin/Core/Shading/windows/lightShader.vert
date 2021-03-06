#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexcoord;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec2 aUV;

out vec2 vTexcoord; // for basic 2D / 3D objects
out vec3 vColor;
out vec3 vNormal;
out vec2 vUV; // for models
out vec3 FragPos;
out vec3 vPos;
uniform mat4 projection, model, view;

// Lights attributes
uniform vec3 lightColor, viewPos, lightPos, viewFront;

out vec3 vLightColor, vViewPos, vLightPos, vViewFront;

void main()
{
    vPos = vec3(model * vec4(aPos, 1.0));
    vTexcoord = aTexcoord;
    vColor = aColor;
    vNormal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    vUV = aUV;

    vLightColor = lightColor;
    vViewPos = viewPos;
    vLightPos = lightPos;
    vViewFront = viewFront;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}