#pragma once

#include "../ECS.h"
#include "../graphics/Shader.h"
#include "TransformComponent.h"

namespace gr
{
    enum Basic2DGeometryShapes
    {
        TRIANGLE,
        SQUARE
    };

    class Textured2DGeometry : public Component
    {
    private:
        unsigned int _texture;
        unsigned int _vao, _vbo;
        Shader* _shader;
        glm::mat4 _m;
        TransformComponent* _transform;
        const char* _file;
        Basic2DGeometryShapes _shapes;
        glm::vec3 _lColor, _lPos, _cPos, _cFront;

    public:
        Textured2DGeometry(const char* file, Basic2DGeometryShapes shape);

        unsigned int GetBuffer();
        Shader* GetShader();

        void SetLightAttribute(glm::vec3 color, glm::vec3 pos, glm::vec3 camPos, glm::vec3 camFront);

        void init() override;
        void draw() override;
        void destroyGL() override;
    };
    
}