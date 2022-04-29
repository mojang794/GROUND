#pragma once

#include "../ECS.h"
#include "TransformComponent.h"
#include "../graphics/Shader.h"

namespace gr {
    enum Basic3DGeometryShapes
    {
        CUBE,
        PYRAMID
    };

    enum Basic3DGeometryRotation
    {
        X,
        Y,
        Z
    };

    class Basic3DGeometry : public Component
    {
    private:
        TransformComponent* transform;
        glm::mat4 proj, view, model;
        unsigned int VAO, VBO;
        gr::Shader* shader;
        Basic3DGeometryShapes types;
        Basic3DGeometryRotation pos;

    private: // Lights attribute
        glm::vec3 lColor, lPos, cPos, cFront;

    public:
        Basic3DGeometry(Basic3DGeometryShapes s, std::string Fshader, std::string Vshader);
        Basic3DGeometry(Basic3DGeometryShapes s, Basic3DGeometryRotation p, std::string Fshader, std::string Vshader);

        unsigned int GetBuffer() const;
        gr::Shader *GetShader() const;

        void SetProjectionView(glm::mat4 p, glm::mat4 v);
        void SetLightAttribute(glm::vec3 color, glm::vec3 pos, glm::vec3 camPos, glm::vec3 camFront);

        void init() override;
        void update(float dt) override;
        void draw() override;
        void destroyGL() override;
    };
}