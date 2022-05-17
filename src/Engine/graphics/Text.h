#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "../system/Color.h"
#include "Shader.h"

namespace gr
{
    /**
     * @brief Text class for display, resize and change color of a text on the screen
     * 
     */
    class Text
    {
    private:
        glm::vec2 _pos, _size;
        unsigned int _text, _vao, _vbo;
        std::string _textString;
        gr::Color _color;
        gr::Shader _shader;
        glm::mat4 _model;

    public:
        Text();
        Text(glm::vec2 position, glm::vec2 size, const char* text);
        Text(glm::vec2 position, glm::vec2 size, const char* text, const char* Vshader, const char* Fshader);
        
        void SetPosition(glm::vec2 position);
        void SetSize(glm::vec2 size);
        void SetTextString(const char* string);

        // in case we don't use a custom shader
        void SetColor(gr::Color color);

        void Draw();
    };
}