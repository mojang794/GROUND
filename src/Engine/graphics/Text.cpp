#include "Text.h"
#include "Shapes.h"

namespace gr
{
    Text::Text()
    {
        
    }
    
    Text::Text(glm::vec2 position, glm::vec2 size, const char* text)
        : _pos(position), _size(size), _textString(text)
    {
        std::string V = R"END(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            layout(location = 0) in vec2 aTexcoords;

            uniform mat4 model;

            out vec3 vPos;
            out vec2 vTexcoords;

            void main()
            {
                vPos = aPos;
                vTexcoords = aTexcoords;
                gl_Position = model * vec4(aPos, 1.0);
            }

        )END";   
        std::string F = R"END()END";   
    }
    
    Text::Text(glm::vec2 position, glm::vec2 size, const char* text, const char* Vshader, const char* Fshader)
        : _pos(position), _size(size), _textString(text)
    {
        
    }
    
    void Text::SetPosition(glm::vec2 position)
    {
        
    }

    void Text::SetSize(glm::vec2 size)
    {
        
    }
    
    void Text::SetTextString(const char* string)
    {
        
    }
    
    void Text::SetColor(gr::Color color)
    {
        
    }
    
    void Text::Draw()
    {
        
    }
}