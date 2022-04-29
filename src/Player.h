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
    Player(std::map<std::string, int> keys, gr::Manager* m);
    ~Player();

    void init();
    void update(float dt);
    void UpdateDraw();

    glm::mat4 GetProjection(float w, float y) const;
    glm::mat4 GetView() const;
    glm::vec3 GetFront() const;
    gr::TransformComponent* GetTransform() const;

    glm::vec3 lightColor;

private:
    gr::Camera* camera;
    gr::Joypad joypad;
    std::map<std::string, int> _keys;
    gr::Entity* ui;
    glm::vec3 _objectColor;
    gr::TransformComponent* p_transform;
};