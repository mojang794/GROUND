#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "../system/Color.h"
#include "Shader.h"
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace gr
{
    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };

    /**
     * @brief Text class for display, resize and change color of a text on the screen
     * 
     */
    class Text
    {
    public:
        Text(glm::vec2 w_size, glm::vec2 position, const char* text, const char* font, float scale);
        
        void SetPosition(glm::vec2 position);
        void SetText(std::string text);
        // in case we don't use a custom shader
        void SetColor(gr::Color color);

        void Draw();
        
    private:
        float _scale;
        unsigned int _vao, _vbo;
        std::map<char, Character> _chars;
        std::string _textString, _font;
        glm::vec2 _pos;
        gr::Color _color;
        gr::Shader *_shader;
        FT_Face face;
    };
}