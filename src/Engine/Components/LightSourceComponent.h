#pragma once

#include "../ECS.h"
#include "../graphics/Shader.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gr {
    class LightSourceComponent : public Component
    {
    private:
        unsigned int VAO, VBO;
        gr::Shader* shader;
        TransformComponent* transform;
        glm::mat4 projection, view;

    public:
        LightSourceComponent() = default;

        void SetProjectionView(glm::mat4 p, glm::mat4 v);
        gr::Shader* getShader();

        void init() override;
        void draw() override;
        void destroyGL() override;

    public:
        glm::vec3 LightColor;
    };
}