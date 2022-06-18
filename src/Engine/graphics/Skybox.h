#pragma once

#include "Shader.h"
#include <vector>

namespace gr
{
    class SkyBox
    {
    public:
        /**
         * @brief Construct a new Sky Box object
         * 
         * @param Vertexpath vertex shader path
         * @param Fragmentpath fragment shader path
         * @param files cube map files. Correct loading path: { right, left, top, bottom, front, back }
         */
        SkyBox(std::string Vertexpath, std::string Fragmentpath, std::vector<std::string> files);
        ~SkyBox();

        void Draw();

        /**
         * @brief Set the projection and the view for 3D
         * 
         * @param projection 
         * @param view 
         */
        void SetVP(glm::mat4 projection, glm::mat4 view);

    private:
        unsigned int _skyboxTexture, _skyboxVAO, _skyboxVBO;
        gr::Shader* _shader;
        glm::mat4 _projection, _view;
    };
}