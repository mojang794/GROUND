#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

namespace engine
{
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

        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

        void setVec2(const std::string& name, const glm::vec2& value) const;
        void setVec2(const std::string& name, float x, float y) const;
        void setVec3(const std::string& name, const glm::vec3& value) const;
        void setVec3(const std::string& name, float x, float y, float z) const;
        void setVec4(const std::string& name, const glm::vec4& value) const;
        void setVec4(const std::string& name, float x, float y, float z, float w);
        
        void setMat2(const std::string& name, const glm::mat2& mat) const;
        void setMat3(const std::string& name, const glm::mat3& mat) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;
    };
}

