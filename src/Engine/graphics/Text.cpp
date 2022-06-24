#include "Text.h"
#include "Shapes.h"
#include "../GR_cross_definitions.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace gr
{
    Text::Text(glm::vec2 w_size, glm::vec2 position, const char *text, const char* font, float scale)
    {
#ifdef _WIN32
        std::string V = R"END(
            #version 330 core
            layout(location = 0) in vec4 vertex;

            uniform mat4 projection;

            out vec2 vTexcoords;

            void main()
            {
                vTexcoords = vertex.zw;
                gl_Position = projection * vec4(vertex.xy, 1.0, 1.0);
            }

        )END";

        std::string F = R"END(
            #version 330 core
            out vec4 FragColor;

            in vec2 vTexcoords;

            uniform sampler2D uTexture;
            uniform vec3 uColor;

            void main()
            {
                vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTexture, vTexcoords).r);
                FragColor = vec4(uColor, 1.0) * sampled;
            }
        )END";
#else
        std::string V = R"END(
            #version 120
            attribute vec4 vertex;

            uniform mat4 model;

            varying vec2 vTexcoords;

            void main()
            {
                vTexcoords = vertex.zw;
                gl_Position = model * vec4(vertex.xy, 1.0, 1.0);
            }

        )END";

        std::string F = R"END(
            #version 120

            varying vec2 vTexcoords;

            uniform sampler2D uTexture;
            uniform vec3 uColor;

            void main()
            {
                vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTexture, vTexcoords).r);
                gl_FragColor = vec4(uColor, 1.0) * sampled;
            }
        )END";
#endif
        _pos = position;
        _textString = text;
        _font = font;
        _scale = scale;

        this->_shader = new gr::Shader(V, F);
        this->_shader->use();
        glm::mat4 projection = glm::ortho(0.0f, w_size.x, 0.0f, w_size.y);
        this->_shader->setMat4("projection", projection);
        
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            gr::LogError("Cannot load Freetype");
        }
        GR_ASSERT(!FT_Init_FreeType(&ft));
        
        if (FT_New_Face(ft, _font.c_str(), 0, &face))
        {
            gr::LogWarning((std::string("Cannot load the font ").append(_font)).c_str());
        }
        else {
            gr::Log((std::string("Loaded font: ").append(_font)).c_str());
            FT_Set_Pixel_Sizes(face, 0, 48);

            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // load first 128 characters of ASCII set
            for (unsigned char c = 0; c < 128; c++)
            {
                // Load character glyph 
                if (FT_Load_Char(face, c, FT_LOAD_RENDER))
                {
                    gr::LogWarning("Failed to load Glyph");
                    continue;
                }
                // generate texture
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );
                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // now store character for later use
                Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    static_cast<unsigned int>(face->glyph->advance.x)
                };
                this->_chars.insert(std::pair<char, Character>(c, character));
            }
        }
        // glBindTexture(GL_TEXTURE_2D, 0);

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        _shader->setVertexAttrib("vertex", 4, GL_FLOAT, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Text::SetPosition(glm::vec2 position)
    {
        this->_pos = position;
    }
    
    void Text::SetText(std::string text)
    {
        this->_textString = text;
    }

    void Text::SetColor(gr::Color color)
    {
        this->_color = color;
    }

    void Text::Draw()
    {
        this->_shader->use();
        this->_shader->setVec3("uColor", _color.getColor3V());
        glActiveTexture(GL_TEXTURE0);
        this->_shader->setInt("uTexture", 0);
        glBindVertexArray(_vao);
        glm::vec2 pos = _pos;
        // iterate through all characters
        std::string::const_iterator c;
        for (c = _textString.begin(); c != _textString.end(); c++)
        {
            Character ch = this->_chars[*c];

            float xpos = pos.x + ch.Bearing.x * _scale;
            float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * _scale;

            float w = ch.Size.x * _scale;
            float h = ch.Size.y * _scale;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },            
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }           
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, _vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            pos.x += (ch.Advance >> 6) * _scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}