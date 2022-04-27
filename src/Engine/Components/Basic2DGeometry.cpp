#include "Basic2DGeometry.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../graphics/Shapes.h"

Basic2DGeometry::Basic2DGeometry(Basic2DGeometryShapes s, std::string Fshader, std::string Vshader)
{
    this->shader = new engine::Shader(Vshader.c_str(), Fshader.c_str());
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

engine::Shader* Basic2DGeometry::GetShader()
{
    return this->shader;
}

void Basic2DGeometry::init()
{
    transform = &entity->getComponent<TransformComponent>();

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

    glVertexAttribPointer(glGetAttribLocation(shader->ID, "aPos"), 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "aPos"));
    glVertexAttribPointer(glGetAttribLocation(shader->ID, "aColor"), 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "aColor"));
    glVertexAttribPointer(glGetAttribLocation(shader->ID, "aTexcoord"), 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "atexcoord"));
}

void Basic2DGeometry::update(float dt __attribute__((unused)))
{
    
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