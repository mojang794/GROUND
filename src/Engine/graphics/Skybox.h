#pragma once

#include <Shader.h>

namespace gr
{
    class SkyBox
    {
    public:
        SkyBox();

        void Draw();

    private:
        unsigned int _skyboxTexture, _skyboxVAO, _skyboxVBO;

    };
}