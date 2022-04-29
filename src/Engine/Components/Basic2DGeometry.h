#pragma once

#include "../ECS.h"
#include "TransformComponent.h"
#include "../graphics/Shader.h"

namespace gr {

    enum Basic2DGeometryShapes
    {
        TRIANGLE,
        SQUARE
    };

    class Basic2DGeometry : public Component
    {
    private:
        glm::mat4 model;
        TransformComponent *transform;
        unsigned int VAO, VBO;
        Shader *shader;
        Basic2DGeometryShapes types;
        glm::vec3 color;

    public:
        Basic2DGeometry(Basic2DGeometryShapes s, std::string Fshader, std::string Vshader);

        unsigned int GetBuffer() const;
        void SetColor(glm::vec3 c);

        Shader* GetShader();

        void init() override;
        void update(float dt) override;
        void draw() override;
        void destroyGL() override;
    };
}