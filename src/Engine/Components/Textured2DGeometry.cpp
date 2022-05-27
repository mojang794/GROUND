#include "Textured2DGeometry.h"
#include "../GR_cross_definitions.h"
#include "../graphics/Shapes.h"
#include "../graphics/Graphics.h"
#include <glm/gtc/matrix_transform.hpp>

namespace gr
{
    Textured2DGeometry::Textured2DGeometry(const char* file, Basic2DGeometryShapes shape)
        : _file(file), _shapes(shape)
    {
        
    }
    
    unsigned int Textured2DGeometry::GetBuffer()
    {
        return _vbo;
    }
    
    Shader* Textured2DGeometry::GetShader()
    {
        return _shader;
    }
    
    void Textured2DGeometry::SetLightAttribute(glm::vec3 color, glm::vec3 pos, glm::vec3 camPos, glm::vec3 camFront)
    {
        this->_lColor = color;
        this->_lPos = pos;
        this->_cPos = camPos;
        this->_cFront = camFront;
    }
    
    void Textured2DGeometry::init()
    {
        if (!entity->hasComponent<TransformComponent>())
            this->_transform = &entity->addComponent<TransformComponent>();
        else
            this->_transform = &entity->getComponent<TransformComponent>();

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        if (_shapes == Basic2DGeometryShapes::SQUARE) {
            glBufferData(GL_ARRAY_BUFFER, sizeof(gr::shapes2D::square), shapes2D::square, GL_STATIC_DRAW);
        } else {
            glBufferData(GL_ARRAY_BUFFER, sizeof(gr::shapes2D::triangle), shapes2D::triangle, GL_STATIC_DRAW);
        }
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glVertexAttribPointer(glGetAttribLocation(_shader->ID, "aPos"), 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glVertexAttribPointer(glGetAttribLocation(_shader->ID, "aColor"), 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
        glVertexAttribPointer(glGetAttribLocation(_shader->ID, "aNormal"), 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        glVertexAttribPointer(glGetAttribLocation(_shader->ID, "aTexcoord"), 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

        _texture = gr::LoadTexture2D(this->_file);
    }
    
    void Textured2DGeometry::draw()
    {
        _shader->use();
        _m = glm::mat4(1.0);
        _m = glm::translate(_m, _transform->position);
        _m = glm::scale(_m, _transform->size);
        _m = glm::rotate(_m, glm::radians(_transform->angle), glm::vec3(1.0, 1.0, 0.0));
        _shader->setMat4("model", _m);
        glBindTexture(GL_TEXTURE_2D, _texture);
        glBindVertexArray(_vao);
        if (_shapes == SQUARE) {
            glDrawArrays(GL_TRIANGLES, 0, 6);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }
    
    void Textured2DGeometry::destroyGL()
    {
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteTextures(1, &_texture);
    }
}