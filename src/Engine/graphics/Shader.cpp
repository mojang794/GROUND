#include "Shader.h"
#include <fstream>
#include <sstream>
#include <cerrno>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "../GR_cross_definitions.h"

bool gr::Shader::isPredefinedUsed = false;
unsigned int gr::Shader::PredefinedID;

void gr::Shader::CompilePredefinedShader(const char* filePath)
{
    if (!isPredefinedUsed)
    {
        char infoLog[512];
        int success;
        const char* fShaderCode;
        std::string fragString;
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(filePath);
            std::stringstream ss;
            ss << file.rdbuf();
            fragString = ss.str();
            file.close();

            fShaderCode = fragString.c_str();
        } catch(std::exception& e) {
            std::string error = "PREDEFINED SHADER -> COMPILATION ERROR: ";
            error.append(e.what());
            gr::LogError(error.c_str());
        }
        PredefinedID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(PredefinedID, 1, &fShaderCode, NULL);
        glCompileShader(PredefinedID);
        // print compile errors if any
        glGetShaderiv(PredefinedID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(PredefinedID, 512, NULL, infoLog);
            std::cout << "ERROR::PREDEFINED::SHADER -> FRAGMENT::COMPILATION_FAILED\n"
                    << infoLog << std::endl;
        };

        gr::Log("PREDEFINED SHADER TOOLS: TRUE");
    }
}

void gr::Shader::DeletePredefinedShader()
{
    glDeleteShader(PredefinedID);
}

gr::Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    LoadFromFile(vertexPath, fragmentPath);
}

gr::Shader::Shader(std::string VertexStream, std::string FragmentStream)
{
    LoadFromStream(VertexStream.c_str(), FragmentStream.c_str());
}

void gr::Shader::LoadFromFile(const char *vertexPath, const char *fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try // Vertex Shader
    {
        // open files
        vShaderFile.open(vertexPath);
        std::stringstream vShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::stringstream ss;
        ss << "SHADER::FILE_ERROR COMPILATION FAILED IN FILE: " << vertexPath << std::endl << e.what();
        gr::LogError(ss.str().c_str());
    }

    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try // Fragment shader
    {
        // open files
        fShaderFile.open(fragmentPath);
        std::stringstream fShaderStream;
        // read file's buffer contents into streams
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        fShaderFile.close();
        // convert stream into string
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::stringstream ss;
        ss << "SHADER::FILE_ERROR COMPILATION FAILED IN FILE: " << fragmentPath << std::endl << e.what();
        gr::LogError(ss.str().c_str());
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        
        std::stringstream ss;
        ss << "ERROR::SHADER::VERTEX::COMPILATION_FAILED IN FILE " << vertexPath << "\n"
                  << infoLog << std::endl;
        gr::LogError(ss.str().c_str());
    };

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::stringstream ss;
        ss << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED IN FILE " << fragmentPath << "\n"
                  << infoLog << std::endl;
        gr::LogError(ss.str().c_str());
    };

    // shader Program
    ID = glCreateProgram();
    
    glAttachShader(ID, PredefinedID);
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::stringstream ss;
        ss << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << "\n"
                  << infoLog << std::endl;
        gr::LogError(ss.str().c_str());
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void gr::Shader::LoadFromStream(const char *VertexStream, const char *FragmentStream)
{
    const char *vShaderCode = VertexStream;
    const char *fShaderCode = FragmentStream;

    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::stringstream ss;
        ss << "ERROR::SHADER::VERTEX::STREAM::COMPILATION_FAILED" << "\n"
                  << infoLog << std::endl;
        gr::LogError(ss.str().c_str());
    };

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::stringstream ss;
        ss << "ERROR::SHADER::FRAGMENT::STREAM::COMPILATION_FAILED"<< "\n"
                  << infoLog << std::endl;
        gr::LogError(ss.str().c_str());
    };

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::stringstream ss;
        ss << "ERROR::SHADER::PROGRAM::STREAM::LINKING_FAILED" << "\n"
                  << infoLog << std::endl;
        gr::LogError(ss.str().c_str());
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void gr::Shader::use()
{
    glUseProgram(ID);
}

void gr::Shader::Delete()
{
    glDeleteProgram(ID);
}

void gr::Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void gr::Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void gr::Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

// ------------------------------------------------------------------------
void gr::Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void gr::Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void gr::Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void gr::Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void gr::Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void gr::Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void gr::Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void gr::Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void gr::Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void gr::Shader::setVertexAttrib(const char* attribName, short size, unsigned type, int stride, const void* pointer)
{
    glVertexAttribPointer(glGetAttribLocation(ID, attribName), size, type, false, stride, pointer);
    glEnableVertexAttribArray(glGetAttribLocation(ID, attribName));
}