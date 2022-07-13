#include "Billboard.h"
#include "GraphicLoader.h"
#include "Shapes.h"
#include "../GR_cross_definitions.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace gr
{
    Billboard::Billboard(std::string Vertexpath, std::string Fragmentpath, const char* file)
    {
        _shader = new gr::Shader(Vertexpath.c_str(), Fragmentpath.c_str());

        _Texture = gr::LoadTexture2D(file);

        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);
        glGenBuffers(1, &_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gr::shapes2D::square), gr::shapes2D::square, GL_STATIC_DRAW);

        _shader->setVertexAttrib("aPos", 3, GL_FLOAT, sizeof(gr::Vertex), (void*)offsetof(gr::Vertex, position));
        _shader->setVertexAttrib("aColor", 3, GL_FLOAT, sizeof(gr::Vertex), (void*)offsetof(gr::Vertex, color));
        _shader->setVertexAttrib("aNormal", 3, GL_FLOAT, sizeof(gr::Vertex), (void*)offsetof(gr::Vertex, normal));
        _shader->setVertexAttrib("aTexcoord", 2, GL_FLOAT, sizeof(gr::Vertex), (void*)offsetof(gr::Vertex, texCoords));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    Billboard::~Billboard()
    {
        glDeleteBuffers(1, &_VBO);
        glDeleteVertexArrays(1, &_VAO);
        glDeleteTextures(1, &_Texture);
        _shader->Delete();
        delete _shader;
    }
    
    void Billboard::Draw(glm::vec3 position, gr::Camera* camera)
    {
        _shader->use();

        glm::vec3 look = glm::normalize(camera->Position - position);
        glm::vec3 right = glm::cross(camera->Up, look);
        glm::vec3 up2 = glm::cross(look, right);

        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, position);
        model[0] = glm::vec4(right, 0);
        model[1] = glm::vec4(up2, 0);
        model[2] = glm::vec4(look, 0);

        _shader->setMat4("model", model);
        _shader->setMat4("projection", _projection);
        _shader->setMat4("view", _view);

        _shader->setVec3("viewPos", viewPos);
        _shader->setVec3("viewFront", viewFront);
        _shader->setVec3("lightPos", lightPos);
        _shader->setVec3("lightColor", lightColor);
    
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _Texture);
        _shader->setInt("uTexture", 0);
        glBindVertexArray(_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        
    }
    
    void Billboard::SetVP(glm::mat4 projection, glm::mat4 view)
    {
        this->_projection = projection;
        this->_view = view;
    }
    
    void Billboard::SetLightAttributes(glm::vec3 viewFront, glm::vec3 viewPos, glm::vec3 lightPos, glm::vec3 lightColor)
    {
        this->viewFront = viewFront;
        this->viewPos = viewPos;
        this->lightPos = lightPos;
        this->lightColor = lightColor;
    }
    
    unsigned int Billboard::GetTexture() const
    {
        return _Texture;
    }
}