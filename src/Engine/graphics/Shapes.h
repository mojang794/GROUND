#pragma once

#include <glm/glm.hpp>

#include "../system/Vertex.h"

namespace gr {
    namespace shapes3D {
        static Vertex cube[] = {
            // Position                      // Color                              // TexCoord            // Normal
            // 
            // Front
            glm::vec3(-0.5f, -0.5f, -0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3( 0.5f, -0.5f, -0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3( 0.5f,  0.5f, -0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3( 0.5f,  0.5f, -0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3(-0.5f,  0.5f, -0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3(-0.5f, -0.5f, -0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f),
            // Back
            glm::vec3(-0.5f, -0.5f,  0.5f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3( 0.5f, -0.5f,  0.5f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3( 0.5f,  0.5f,  0.5f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3( 0.5f,  0.5f,  0.5f),  Color(0.0f, 1.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3(-0.5f,  0.5f,  0.5f),  Color(0.0f, 1.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3(-0.5f, -0.5f,  0.5f),  Color(0.0f, 1.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f),
            // Left
            glm::vec3(-0.5f,  0.5f,  0.5f),  Color(1.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(-0.5f,  0.5f, -0.5f),  Color(1.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(-0.5f, -0.5f, -0.5f),  Color(1.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(-0.5f, -0.5f, -0.5f),  Color(0.0f, 1.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(-0.5f, -0.5f,  0.5f),  Color(0.0f, 1.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(-0.5f,  0.5f,  0.5f),  Color(0.0f, 1.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f),
            // Right
            glm::vec3( 0.5f,  0.5f,  0.5f),  Color(1.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f),
            glm::vec3( 0.5f,  0.5f, -0.5f),  Color(1.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f),
            glm::vec3( 0.5f, -0.5f, -0.5f),  Color(1.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f,  0.0f,  0.0f),
            glm::vec3( 0.5f, -0.5f, -0.5f),  Color(1.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f,  0.0f,  0.0f),
            glm::vec3( 0.5f, -0.5f,  0.5f),  Color(1.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f,  0.0f,  0.0f),
            glm::vec3( 0.5f,  0.5f,  0.5f),  Color(1.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f),
            // Bottom
            glm::vec3(-0.5f, -0.5f, -0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3( 0.5f, -0.5f, -0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3( 0.5f, -0.5f,  0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3( 0.5f, -0.5f,  0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3(-0.5f, -0.5f,  0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3(-0.5f, -0.5f, -0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            // Top
            glm::vec3(-0.5f,  0.5f, -0.5f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f),
            glm::vec3( 0.5f,  0.5f, -0.5f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f),
            glm::vec3( 0.5f,  0.5f,  0.5f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  1.0f,  0.0f),
            glm::vec3( 0.5f,  0.5f,  0.5f),  Color(0.0f, 1.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f,  1.0f,  0.0f),
            glm::vec3(-0.5f,  0.5f,  0.5f),  Color(0.0f, 1.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f,  1.0f,  0.0f),
            glm::vec3(-0.5f,  0.5f, -0.5f),  Color(0.0f, 1.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f)
        };

        static Vertex pyramid[] = {
            // Position                      // Color                              // TexCoord
            glm::vec3(-0.5f, -0.5f, -0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3( 0.5f, -0.5f, -0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f),
            glm::vec3( 0.0f,  0.5f,  0.0f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f,  0.0f, -1.0f),
            
            glm::vec3(-0.5f, -0.5f,  0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3( 0.5f, -0.5f,  0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f),
            glm::vec3( 0.0f,  0.5f,  0.0f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f,  0.0f,  1.0f),

            glm::vec3(-0.5f, -0.5f, -0.5f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3(-0.5f, -0.5f,  0.5f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3( 0.0f,  0.5f,  0.0f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(0.5f, 1.0f), glm::vec3(-1.0f,  0.0f,  0.0f),

            glm::vec3( 0.5f, -0.5f, -0.5f),  Color(1.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f),
            glm::vec3( 0.5f, -0.5f,  0.5f),  Color(1.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f),
            glm::vec3( 0.0f,  0.5f,  0.0f),  Color(1.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.5f, 1.0f), glm::vec3( 1.0f,  0.0f,  0.0f),
        };

    }

    namespace shapes2D {
        static Vertex square[] = {
            glm::vec3(-0.5f, -0.5f, 0.0f), Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, -1),
            glm::vec3( 0.5f, -0.5f, 0.0f), Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, -1),
            glm::vec3(-0.5f,  0.5f, 0.0f), Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, -1),

            glm::vec3(-0.5f,  0.5f, 0.0f), Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, -1),
            glm::vec3( 0.5f,  0.5f, 0.0f), Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, -1),
            glm::vec3( 0.5f, -0.5f, 0.0f), Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, -1),
        };

        static Vertex plane[] = {
            glm::vec3(-0.5f, 0.0f, -0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3( 0.5f, 0.0f, -0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3( 0.5f, 0.0f,  0.5f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3( 0.5f, 0.0f,  0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3(-0.5f, 0.0f,  0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f,  0.0f),
            glm::vec3(-0.5f, 0.0f, -0.5f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f),
        };

        static Vertex triangle[] = {
            glm::vec3(-0.5f, -0.5f, 0.0f),  Color(1.0f, 0.0f, 0.0f).getColor3V(), glm::vec2(0.0f, 0.0f), glm::vec3(),
            glm::vec3( 0.5f, -0.5f, 0.0f),  Color(0.0f, 1.0f, 0.0f).getColor3V(), glm::vec2(1.0f, 0.0f), glm::vec3(),
            glm::vec3( 0.0f,  0.5f, 0.0f),  Color(0.0f, 0.0f, 1.0f).getColor3V(), glm::vec2(0.5f, 1.0f), glm::vec3(),
        };
    }
}