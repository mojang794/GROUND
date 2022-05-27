#include "Graphics.h"
#include <glad/glad.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <stb_image.h>
#include "../GR_cross_definitions.h"

static std ::vector<std ::string> g_supportExtensions;

namespace gr
{
    bool loadOBJ(
        const char *path,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals)
    {
        gr::Log((std::string("Loading model: ").append(path)).c_str());

        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_uvs;
        std::vector<glm::vec3> temp_normals;

        FILE *file = fopen(path, "r");
        if (file == NULL)
        {
            gr::LogError("Impossible to open the file ! Are you in the right path ?");
            GR_ASSERT(file == NULL);
            getchar();
            return false;
        }

        while (1)
        {

            char lineHeader[128];
            // read the first word of the line
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
                break; // EOF = End Of File. Quit the loop.

            // else : parse lineHeader

            if (strcmp(lineHeader, "v") == 0)
            {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_vertices.push_back(vertex);
            }
            else if (strcmp(lineHeader, "vt") == 0)
            {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
                temp_uvs.push_back(uv);
            }
            else if (strcmp(lineHeader, "vn") == 0)
            {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                temp_normals.push_back(normal);
            }
            else if (strcmp(lineHeader, "f") == 0)
            {
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                if (matches != 9)
                {
                    gr::LogError("File can't be read by our simple parser :-( Try exporting with other options");
                    GR_ASSERT(matches != 9);
                    fclose(file);
                    return false;
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
            else
            {
                // Probably a comment, eat up the rest of the line
                char stupidBuffer[1000];
                fgets(stupidBuffer, 1000, file);
            }
        }

        // For each vertex of each triangle
        for (unsigned int i = 0; i < vertexIndices.size(); i++)
        {

            // Get the indices of its attributes
            unsigned int vertexIndex = vertexIndices[i];
            unsigned int uvIndex = uvIndices[i];
            unsigned int normalIndex = normalIndices[i];

            // Get the attributes thanks to the index
            glm::vec3 vertex = temp_vertices[vertexIndex - 1];
            glm::vec2 uv = temp_uvs[uvIndex - 1];
            glm::vec3 normal = temp_normals[normalIndex - 1];

            // Put the attributes in buffers
            out_vertices.push_back(vertex);
            out_uvs.push_back(uv);
            out_normals.push_back(normal);
        }
        fclose(file);
        gr::Log("Loading finished!");
        return true;
    }

    unsigned int LoadTexture2D(const char *file)
    {
        unsigned int _id;
        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int nrChannels, width, height;
        unsigned char *data = stbi_load(file, &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            gr::LogError("Failed to load texture");
        }
        GR_ASSERT(data);
        stbi_image_free(data);

        return _id;
    }

    unsigned int LoadCubeMap(std::vector<std::string> files)
    {
        unsigned int _id;
        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < files.size(); i++)
        {
            unsigned char *data = stbi_load(files[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                            0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                stbi_image_free(data);
            }
            else
            {
                gr::LogError((std::string("Cubemap tex failed to load at path: ").append(files[i])).c_str());
                stbi_image_free(data);
            }
            GR_ASSERT(data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 

        return _id;  
    }

    void GetSupportExtensions()
    {
        if (!g_supportExtensions.empty())
            return;
        GLint n, i;
        glGetIntegerv(GL_NUM_EXTENSIONS, &n);
        for (i = 0; i < n; i++)
        {
            std ::string extension = (char *)glGetStringi(GL_EXTENSIONS, i);
            g_supportExtensions.push_back(extension);
        }
    }

    // public API
    bool CheckExtension(const std::string &extensionName)
    {
        GetSupportExtensions();

        for (std::size_t i = 0; i < g_supportExtensions.size(); i++)
        {
            if (g_supportExtensions[i] == extensionName)
                return true;
        }
        return false;
    }

    void WriteAllExtension()
    {
        for (std::size_t I = 0; I < g_supportExtensions.size(); I++)
        {
            std::cout << "Exts:" << g_supportExtensions[I].c_str() << "\n";
        }
    }
}