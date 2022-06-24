#include "ModelComponent.h"
#include "../graphics/GraphicLoader.h"
#include "../GR_cross_definitions.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

namespace gr {
    ModelComponent::ModelComponent(const char* Modelpath, const char* Texturepath, std::string Fshader, std::string Vshader, unsigned int Tcount)
    {
        res = gr::loadOBJ(Modelpath, this->vertices, this->uvs, this->normals);
        this->shader = new gr::Shader(Vshader.c_str(), Fshader.c_str());
        this->TextureCount = Tcount;
        this->TexturePath = Texturepath;
    }

    void ModelComponent::SetProjectionView(glm::mat4 p, glm::mat4 v)
    {
        this->projection = p;
        this->view = v;
    }

    void ModelComponent::SetLightAttribute(glm::vec3 color, glm::vec3 pos, glm::vec3 camPos, glm::vec3 camFront)
    {
        this->lColor = color;
        this->lPos = pos;
        this->cPos = camPos;
        this->cFront = camFront;
    }

    gr::Shader* ModelComponent::GetShader()
    {
        return this->shader;
    }

    void ModelComponent::init()
    {
        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        else { transform = &entity->getComponent<TransformComponent>(); }

        if (!res) {
            gr::LogError("ERROR! cannot load the 3D model! No source file on directory!");
            return;
        }
        else
        {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

            glGenBuffers(1, &UVBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);
            glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

            glGenBuffers(1, &NormalBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
            shader->setVertexAttrib("aPos", 3, GL_FLOAT, 0, (void*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);
            shader->setVertexAttrib("aUV", 3, GL_FLOAT, 0, (void*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
            shader->setVertexAttrib("aNormal", 3, GL_FLOAT, 0, (void*)0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glGenTextures(1, &TextureID);
            glBindTexture(GL_TEXTURE_2D, TextureID);

            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int width, height, nrChannels;
            unsigned char* data = stbi_load(TexturePath.c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Failed to load texture" << std::endl;
            }
            stbi_image_free(data);
        }
    }

    void ModelComponent::draw()
    {
        shader->use();

        model = glm::mat4(1.0f);
        model = glm::translate(model, transform->position);
        model = glm::rotate(model, glm::radians(transform->angle), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, transform->size);

        shader->setMat4("model", model);
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);

        shader->setVec3("lightPos", lPos);
        shader->setVec3("lightColor", lColor);
        shader->setVec3("viewPos", cPos);
        shader->setVec3("viewFront", cFront);

        glActiveTexture(TextureCount);
        glBindTexture(GL_TEXTURE_2D, TextureID);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        glBindVertexArray(0);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void ModelComponent::destroyGL()
    {
        glDeleteBuffers(1, &NormalBuffer);
        glDeleteBuffers(1, &UVBuffer);
        glDeleteBuffers(1, &VertexBuffer);
        glDeleteVertexArrays(1, &VAO);
        glDeleteTextures(1, &TextureID);
        shader->Delete();

        delete shader;
    }
}