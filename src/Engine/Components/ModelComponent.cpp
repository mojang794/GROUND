#include "ModelComponent.h"
#include "../graphics/Graphics.h"
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
        transform = &entity->getComponent<TransformComponent>();

        if (!res) {
            std::cerr << "ERROR! cannot load the 3D model! No source file on directory!" << std::endl;
            throw "ERROR! cannot load the 3D model! No source file on directory!";
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
            glVertexAttribPointer(glGetAttribLocation(shader->ID, "aPos"), 3, GL_FLOAT, false, 0, (void*)0);
            glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "aPos"));

            glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);
            glVertexAttribPointer(glGetAttribLocation(shader->ID, "aUV"), 2, GL_FLOAT, false, 0, (void*)0);
            glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "aUV"));

            glBindBuffer(GL_ARRAY_BUFFER, NormalBuffer);
            glVertexAttribPointer(glGetAttribLocation(shader->ID, "aNormal"), 3, GL_FLOAT, false, 0, (void*)0);
            glEnableVertexAttribArray(glGetAttribLocation(shader->ID, "aNormal"));

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

    void ModelComponent::update(float dt __attribute__((unused)))
    {
        
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