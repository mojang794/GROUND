#pragma once

#include "../ECS.h"
#include <glm/glm.hpp>
#include <iostream>

class TransformComponent : public Component
{
public:
    glm::vec3 position, size;
    float angle;

    TransformComponent()
    {
        position.x = 0.f;
        position.y = 0.f;
        position.z = 0.f;
        size = glm::vec3(1.0, 1.0, 1.0);
        angle = 0.0f;
    }

    // No 3D-World
    TransformComponent(float x, float y)
    {
        position = glm::vec3(x, y, 0.0);
        size = glm::vec3(1.0, 1.0, 1.0);
        angle = 0.0f;
    }

    // With 3D-World
    TransformComponent(float x, float y, float z)
    {
        position = glm::vec3(x, y, z);
        size = glm::vec3(1.0, 1.0, 1.0);
        angle = 0.0f;
    }

    // With 3D-World + object scale
    TransformComponent(float x, float y, float z, glm::vec3 size)
    {
        position = glm::vec3(x, y, z);
        this->size = size;
        angle = 0.0f;
    }

    // With 3D-World + object scale + object rotate angle
    TransformComponent(float x, float y, float z, glm::vec3 size, float ng)
    {
        position = glm::vec3(x, y, z);
        this->size = size;
        angle = ng;
    }

    friend std::ostream& operator<<(std::ostream& os, const TransformComponent& dt) {
        os << "Transform Component: " << std::endl
           << "Position: " << std::endl
           << "     X: " << dt.position.x << std::endl
           << "     Y: " << dt.position.y << std::endl
           << "     Z: " << dt.position.z << std::endl
           << "Size: " << dt.angle << std::endl
           << "     X: " << dt.size.x << std::endl
           << "     Y: " << dt.size.y << std::endl
           << "     Z: " << dt.size.z << std::endl
           << "Angle: " << dt.angle << std::endl;
        
        return os;
    }
};