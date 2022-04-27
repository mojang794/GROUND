#pragma once

#include "../ECS.h"
#include "../graphics/Shader.h"
#include "TransformComponent.h"

class ModelComponent : public Component
{
private: // General...
    bool res;
    std::string TexturePath;

private: // Components
    TransformComponent* transform;

private: // Texture, VAO, VBO, Matrix
    glm::mat4 projection, model, view;
    unsigned int NormalBuffer, UVBuffer, VertexBuffer, VAO, TextureID, TextureCount;
    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;

private: // Lights attribute
    engine::Shader* shader; 
    glm::vec3 lColor, lPos, cPos, cFront;

public:
    ModelComponent(const char* Modelpath, const char* Texturepath, std::string Fshader, std::string Vshader, unsigned int Tcount);

    void SetProjectionView(glm::mat4 p, glm::mat4 v);
    void SetLightAttribute(glm::vec3 color, glm::vec3 pos, glm::vec3 camPos, glm::vec3 camFront);

    engine::Shader* GetShader();

    void init() override;
    void update(float dt) override;
    void draw() override;
    void destroyGL() override;
};