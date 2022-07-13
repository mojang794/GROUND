#pragma once

#include "Shader.h"
#include "../Camera.h"
#include <vector>

namespace gr
{
    class Billboard
    {
    public:
        Billboard(std::string Vertexpath, std::string Fragmentpath, const char* file);
        ~Billboard();

        void Draw(glm::vec3 position, gr::Camera* camera);

        /**
         * @brief Set the projection and the view for 3D
         * 
         * @param projection 
         * @param view 
         */
        void SetVP(glm::mat4 projection, glm::mat4 view);
        void SetLightAttributes(glm::vec3 viewFront, glm::vec3 viewPos, glm::vec3 lightPos, glm::vec3 lightColor);

        unsigned int GetTexture() const;

    private:
        unsigned int _Texture, _VAO, _VBO;
        gr::Shader* _shader;
        glm::mat4 _projection, _view;
        glm::vec3 viewFront, viewPos, lightPos, lightColor;
    };
}