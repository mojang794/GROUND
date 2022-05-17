#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>

namespace gr
{
    /**
     * @brief This function load a 3D model.
     * 
     * This only support OBJ file extension, and the model must be exported with Normals and with
     * Triangles
     */
    bool loadOBJ(
        const char *path,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals);

    /**
     * @brief This function load a 2D texture
     */
    unsigned int LoadTexture2D(int width, int height, const char* file);


    // static API
    void GetSupportExtensions();
    void WriteAllExtension();
    // public API
    bool CheckExtension(const std::string &extensionName);
}