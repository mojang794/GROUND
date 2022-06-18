#include "Collision.h"

namespace gr
{
    bool Collision::AABB(Entity* a, Entity* b)
    {
        TransformComponent* one = &a->getComponent<TransformComponent>();
        TransformComponent* two = &b->getComponent<TransformComponent>();

        bool collisionX = one->position.x + one->size.x >= two->position.x &&
            two->position.x + two->size.x >= one->position.x;
        // collision y-axis?
        bool collisionY = one->position.y + one->size.y >= two->position.y &&
            two->position.y + two->size.y >= one->position.y;
                
        bool collisionZ = one->position.z + one->size.z >= two->position.z &&
            two->position.z + two->size.z >= one->position.z;

        return collisionX && collisionY && collisionZ;
    }

    bool Collision::AABB(TransformComponent* one, TransformComponent* two)
    {
        bool collisionX = one->position.x + one->size.x >= two->position.x &&
            two->position.x + two->size.x >= one->position.x;
        // collision y-axis?
        bool collisionY = one->position.y + one->size.y >= two->position.y &&
            two->position.y + two->size.y >= one->position.y;
            
        bool collisionZ = one->position.z + one->size.z >= two->position.z &&
            two->position.z + two->size.z >= one->position.z;
        
        return collisionX && collisionY && collisionZ;
    }

    bool Collision::AABB(TransformComponent* one, Entity* b)
    {
        TransformComponent* two = &b->getComponent<TransformComponent>();

        bool collisionX = one->position.x + one->size.x >= two->position.x &&
             two->position.x + two->size.x >= one->position.x;
        // collision y-axis?
        bool collisionY = one->position.y + one->size.y >= two->position.y &&
            two->position.y + two->size.y >= one->position.y;
                
        bool collisionZ = one->position.z + one->size.z >= two->position.z &&
            two->position.z + two->size.z >= one->position.z;
        
        return collisionX && collisionY && collisionZ;
    }
}