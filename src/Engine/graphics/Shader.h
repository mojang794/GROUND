#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

namespace gr
{
    // Basic shader class for loading and pass uniforms in shaders
    class Shader
    {
    private:
        static bool isPredefinedUsed;
        static unsigned int PredefinedID;

    public:
        static void CompilePredefinedShader(const char*);
        static void DeletePredefinedShader();

        // the program ID
        unsigned int ID;

        Shader() = default;
        Shader(const char* vertexPath, const char* fragmentPath);
        Shader(std::string VertexStream, std::string FragmentStream);

        void LoadFromFile(const char* vertexPath, const char* fragmentPath);
        void LoadFromStream(const char* VertexStream, const char* FragmentStream);

        void use();
        void Delete();
        // Normal types
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        // Vectors
        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w);
        // Matrix
        void setMat2(const std::string& name, const glm::mat2& mat) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;
    
    public:
        /**
         * @brief Set the Vertex Attrib object
         * 
         * @param attribName the attribute name
         * @param size size of the attribute (example, for "vec3" set 3)
         * @param type the gl type (example: GL_FLOAT, GL_UNSIGNED_INT)
         * @param stride the stride of the attribute (if using gr::Vertex, set 'sizeof(gr::Vertex)')
         * @param pointer the pointer of the data (if using gr::Vertex, use '(void*)offsetof(gr::Vertex, #data#))
         */
        void setVertexAttrib(const char* attribName, short size, unsigned type, int stride, const void* pointer);
    };
}

