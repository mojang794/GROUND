#include "Skybox.h"
#include "GraphicLoader.h"
#include "Shapes.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace gr
{
    SkyBox::SkyBox(std::string Vertexpath, std::string Fragmentpath, std::vector<std::string> files)
    {
        _shader = new gr::Shader(Vertexpath.c_str(), Fragmentpath.c_str());

        _skyboxTexture = gr::LoadCubeMap(files);

        glGenVertexArrays(1, &_skyboxVAO);
        glBindVertexArray(_skyboxVAO);
        glGenBuffers(1, &_skyboxVBO);
        glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(gr::shapes3D::cube), gr::shapes3D::cube, GL_STATIC_DRAW);

        _shader->setVertexAttrib("aPos", 3, GL_FLOAT, sizeof(gr::Vertex), (void*)offsetof(gr::Vertex, position));

        _shader->use();
        _shader->setInt("skybox", 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    
    SkyBox::~SkyBox()
    {
        glDeleteBuffers(1, &_skyboxVBO);
        glDeleteVertexArrays(1, &_skyboxVAO);
        glDeleteTextures(1, &_skyboxTexture);
        _shader->Delete();
        delete _shader;
    }
    
    void SkyBox::Draw()
    {
        _shader->use();

        _shader->setMat4("projection", _projection);
        _shader->setMat4("view", _view);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTexture);
        glBindVertexArray(_skyboxVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    
    void SkyBox::SetVP(glm::mat4 projection, glm::mat4 view)
    {
        this->_projection = projection;
        this->_view = glm::mat4(glm::mat3(view));
    }
}