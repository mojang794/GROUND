#include "LightSourceComponent.h"
#include <glad/glad.h>
#include "../graphics/Shapes.h"

namespace gr {

    void LightSourceComponent::init()
    {
        const char* vShader = R"END(
            
            #version 330 core
            layout(location=0) in vec3 aPos;

            uniform mat4 projection, view, model;

            void main()
            {
                gl_Position = projection * view * model * vec4(aPos, 1.0);
            }

            )END";
        
        const char* fShader = R"END(
            
            #version 330 core

            uniform vec3 lightColor;

            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(1.0);
            }

            )END";

        if (!entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        else { transform = &entity->getComponent<TransformComponent>(); }

        std::string _v = vShader;
        std::string _f = fShader;

        this->shader = new gr::Shader(_v, _f);

        glGenVertexArrays(1, &this->VAO);
        glBindVertexArray(this->VAO);

        glGenBuffers(1, &this->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(shapes3D::cube), shapes3D::cube, GL_STATIC_DRAW);

        shader->setVertexAttrib("aPos", 3, GL_FLOAT, sizeof(gr::Vertex), (void*)offsetof(gr::Vertex, position));
    }

    void LightSourceComponent::draw()
    {
        shader->use();
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform->position);
        model = glm::scale(model, transform->size);

        shader->setMat4("model", model);

        shader->setVec3("lightColor", this->LightColor);

        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }

    void LightSourceComponent::destroyGL()
    {
        glDeleteBuffers(1,  &this->VBO);
        glDeleteVertexArrays(1,  &this->VAO);
        shader->Delete();
    }

    void LightSourceComponent::SetProjectionView(glm::mat4 p, glm::mat4 v)
    {
        this->projection = p;
        this->view = v;
    }

    gr::Shader* LightSourceComponent::getShader()
    {
        return shader;
    }

}