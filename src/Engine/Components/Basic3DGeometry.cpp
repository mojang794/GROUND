#include "Basic3DGeometry.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../graphics/Shapes.h"

Basic3DGeometry::Basic3DGeometry(Basic3DGeometryShapes s, std::string Fshader, std::string Vshader)
{
    this->shader = new engine::Shader(Vshader.c_str(), Fshader.c_str());
    types = s;
    pos = Basic3DGeometryRotation::X;
}

Basic3DGeometry::Basic3DGeometry(Basic3DGeometryShapes s, Basic3DGeometryRotation p, std::string Fshader, std::string Vshader)
{
    this->shader = new engine::Shader(Vshader.c_str(), Fshader.c_str());
    types = s;
    pos = p;
}

unsigned int Basic3DGeometry::GetBuffer() const
{
    return this->VBO;
}

engine::Shader* Basic3DGeometry::GetShader() const
{
    return shader;
}

void Basic3DGeometry::SetProjectionView(glm::mat4 p, glm::mat4 v)
{
    this->proj = p;
    this->view = v;
}

void Basic3DGeometry::SetLightAttribute(glm::vec3 color, glm::vec3 pos, glm::vec3 camPos, glm::vec3 camFront)
{
    lColor = color;
    lPos = pos;
    cPos = camPos;
    cFront = camFront;
}

void Basic3DGeometry::init()
{
    transform = &entity->getComponent<TransformComponent>();

    glGenVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    switch (types)
    {
    case CUBE:
        glBufferData(GL_ARRAY_BUFFER, sizeof(shapes3D::cube), shapes3D::cube, GL_STATIC_DRAW);
        break;
    case PYRAMID:
        glBufferData(GL_ARRAY_BUFFER, sizeof(shapes3D::pyramid), shapes3D::pyramid, GL_STATIC_DRAW);
        break;
    }

    glVertexAttribPointer(glGetAttribLocation(shader->ID, "aPos"), 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "aPos"));
    glVertexAttribPointer(glGetAttribLocation(shader->ID, "aColor"), 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "aColor"));
    glVertexAttribPointer(glGetAttribLocation(shader->ID, "aTexcoord"), 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "aTexcoord"));
    glVertexAttribPointer(glGetAttribLocation(shader->ID, "aNormal"), 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "aNormal"));
}

void Basic3DGeometry::update(float dt __attribute__((unused)))
{
    
}

void Basic3DGeometry::draw()
{
    shader->use();
    shader->setMat4("projection", proj);
    shader->setMat4("view", view);
    shader->setVec3("lightColor", lColor);
    shader->setVec3("lightPos", lPos);
    shader->setVec3("viewPos", cPos);
    shader->setVec3("viewFront", cFront);

    glBindVertexArray(this->VAO);

    model = glm::mat4(1.0f);
    model = glm::scale(model, transform->size);
    model = glm::translate(model, transform->position);
    switch(pos)
    {
    case X:
        model = glm::rotate(model, glm::radians(transform->angle), glm::vec3(1.0f, 0.0f, 0.0f));
        break;
    case Y:
        model = glm::rotate(model, glm::radians(transform->angle), glm::vec3(0.0f, 1.0f, 0.0f));
        break;
    case Z:
        model = glm::rotate(model, glm::radians(transform->angle), glm::vec3(0.0f, 0.0f, 1.0f));
        break;
    
    }
    shader->setMat4("model", model);

    switch (types)
    {
    case CUBE:
        glDrawArrays(GL_TRIANGLES, 0, 36);   
        break;
    case PYRAMID:
        glDrawArrays(GL_TRIANGLES, 0, 18);
        break;
    }
}

void Basic3DGeometry::destroyGL()
{
    glDeleteBuffers(1, &this->VBO);
    glDeleteVertexArrays(1, &this->VAO);
    shader->Delete();
}



