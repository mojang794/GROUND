#pragma once

#include "../ECS.h"
#include "../graphics/Shader.h"
#include "TransformComponent.h"

namespace gr
{
    class Textured2DGeometry : public Component
    {
    private:
        unsigned int _texture;
        unsigned int _vao, _vbo;
        Shader* _shader;
        glm::mat4 _m, _v, _p;
        TransformComponent* _transform;
        const char* _file;
        
        glm::vec3 _lColor, _lPos, _cPos, _cFront;

    public:
        Textured2DGeometry(const char* file);

        unsigned int GetBuffer();
        Shader* GetShader();

        void SetProjectionView(glm::mat4 p, glm::mat4 v);
        void SetLightAttribute(glm::vec3 color, glm::vec3 pos, glm::vec3 camPos, glm::vec3 camFront);

        void init() override;
        void draw() override;
        void destroyGL() override;
    };
    
}