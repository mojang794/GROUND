#pragma once

#include "../ECS.h"
#include "TransformComponent.h"
#include "../graphics/Shader.h"
#include "GeometryShapes.h"

namespace gr {

    class Basic2DGeometry : public Component
    {
    private:
        glm::mat4 model;
        TransformComponent *transform;
        unsigned int VAO, VBO;
        Shader *shader;
        Basic2DGeometryShapes types;
        glm::vec3 color;
        glm::mat4 projection, view;

    public:
        Basic2DGeometry(Basic2DGeometryShapes s, std::string Fshader, std::string Vshader);
        bool implement3D;

        unsigned int GetBuffer() const;
        void SetColor(glm::vec3 c);
        void SetViewProjection(glm::mat4 p, glm::mat4 v);

        Shader* GetShader();

        void init() override;
        void draw() override;
        void destroyGL() override;
    };
}