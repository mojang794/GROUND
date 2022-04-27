#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>

namespace engine
{
    bool loadOBJ(
        const char *path,
        std::vector<glm::vec3> &out_vertices,
        std::vector<glm::vec2> &out_uvs,
        std::vector<glm::vec3> &out_normals);

    // static API
    void GetSupportExtensions();
    void WriteAllExtension();
    // public API
    bool CheckExtension(const std::string &extensionName);
}