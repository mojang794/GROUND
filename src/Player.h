#pragma once

#include "Engine/Camera.h"
#include "Engine/Joypad.hpp"
#include "Engine/ECS.h"
#include "Engine/Components/TransformComponent.h"
#include <glm/glm.hpp>
#include <map>

class Player
{
public:
    Player(std::map<std::string, int> keys, Manager* m);
    ~Player();

    void init();
    void update(float dt);
    void UpdateDraw();

    glm::mat4 GetProjection(float w, float y) const;
    glm::mat4 GetView() const;
    glm::vec3 GetFront() const;
    TransformComponent* GetTransform() const;

    glm::vec3 lightColor;

private:
    engine::Camera* camera;
    engine::Joypad joypad;
    std::map<std::string, int> _keys;
    Entity* ui;
    glm::vec3 _objectColor;
};