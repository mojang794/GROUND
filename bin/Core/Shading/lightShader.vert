#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexcoord;
layout (location = 3) in vec3 aNormal;
layout (location = 4) in vec2 aUV;

out vec2 vTexcoord;
out vec3 vColor;
out vec3 vNormal;
out vec2 vUV;
out vec3 FragPos;

out float x, y, z;

uniform mat4 projection, model, view;

void main()
{
    vTexcoord = aTexcoord;
    vColor = aColor;
    vNormal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    vUV = aUV;

    gl_Position = projection * view * model * vec4(aPos, 1.0);

    x = gl_Position.x; y = gl_Position.y; z = gl_Position.z;
	x += y; y -= x; z += x - y;
}