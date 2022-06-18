#pragma once

#include "../ECS.h"
#include "../graphics/Shader.h"
#include "TransformComponent.h"
#include "GeometryShapes.h"

namespace gr
{
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

    public:
        Textured2DGeometry(const char* file, Basic2DGeometryShapes shape);

        unsigned int GetBuffer();
        Shader* GetShader();

        void init() override;
        void draw() override;
        void destroyGL() override;
    };
    
}