#include "Basic2DGeometry.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../graphics/Shapes.h"

namespace gr {

    Basic2DGeometry::Basic2DGeometry(Basic2DGeometryShapes s, std::string Fshader, std::string Vshader)
    {
        this->shader = new gr::Shader(Vshader.c_str(), Fshader.c_str());
        types = s;
    }

    unsigned int Basic2DGeometry::GetBuffer() const
    {
        return this->VBO;
    }

    void Basic2DGeometry::SetColor(glm::vec3 c)
    {
        this->color = c;
    }

    gr::Shader* Basic2DGeometry::GetShader()
    {
        return this->shader;
    }

    void Basic2DGeometry::init()
    {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        else { transform = &entity->getComponent<TransformComponent>(); }

        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

        switch (types)
        {
        case SQUARE:
            glBufferData(GL_ARRAY_BUFFER, sizeof(shapes2D::square), shapes2D::square, GL_STATIC_DRAW);
            break;
        case TRIANGLE:
            glBufferData(GL_ARRAY_BUFFER, sizeof(shapes2D::triangle), shapes2D::triangle, GL_STATIC_DRAW);
            break;
        }

        shader->setVertexAttrib("aPos", 3, GL_FLOAT, sizeof(gr::Vertex), (void*)offsetof(gr::Vertex, position));
        shader->setVertexAttrib("aColor", 3, GL_FLOAT, sizeof(gr::Vertex), (void*)offsetof(gr::Vertex, color));
    }

    void Basic2DGeometry::draw()
    {
        shader->use();
        shader->setVec3("ObjectColor", color);

        model = glm::mat4(1.0f);
        model = glm::translate(model, transform->position);
        model = glm::scale(model, transform->size);

        shader->setMat4("model", model);

        glBindVertexArray(this->VAO);
        switch (types)
        {
        case SQUARE:
            glDrawArrays(GL_TRIANGLES, 0, 6);   
            break;
        case TRIANGLE:
            glDrawArrays(GL_TRIANGLES, 0, 3);
            break;
        }
    }

    void Basic2DGeometry::destroyGL()
    {
        glDeleteBuffers(1, &this->VBO);
        glDeleteVertexArrays(1, &this->VAO);
        shader->Delete();
    }
}