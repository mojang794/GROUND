#include "Textured2DGeometry.h"
namespace gr
{
    Textured2DGeometry::Textured2DGeometry(const char* file)
        : _file(file)
    {
        
    }
    
    unsigned int Textured2DGeometry::GetBuffer()
    {
        return _vbo;
    }
    
    Shader* Textured2DGeometry::GetShader()
    {
        return _shader;
    }
    
    void Textured2DGeometry::SetProjectionView(glm::mat4 p, glm::mat4 v)
    {
        this->_p = p;
        this->_v = v;
    }
    
    void Textured2DGeometry::SetLightAttribute(glm::vec3 color, glm::vec3 pos, glm::vec3 camPos, glm::vec3 camFront)
    {
        this->_lColor = color;
        
    }
    
    void Textured2DGeometry::init()
    {
        
    }
    
    void Textured2DGeometry::draw()
    {
        
    }
    
    void Textured2DGeometry::destroyGL()
    {
        
    }
}