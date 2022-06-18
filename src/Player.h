#pragma once

#include "Engine/Camera.h"
#include "Engine/ECS.h"
#include "Engine/Components/TransformComponent.h"
#include "Engine/utils/ConfigParser.h"
#include <glm/glm.hpp>
#include <map>
#include <GLFW/glfw3.h>

class Player
{
public:
    Player(gr::ConfigFile<int>& keys, gr::Manager* m);
    ~Player();

    void init();
    void update(float dt, GLFWwindow* window);
    void UpdateDraw();

    glm::mat4 GetProjection(float w, float y) const;
    glm::mat4 GetView() const;
    glm::vec3 GetFront() const;
    gr::TransformComponent* GetTransform() const;

    glm::vec3 lightColor;
    glm::ivec2 WindowSize;

private:
    gr::Camera* camera;
    gr::ConfigFile<int> _keys;
    gr::Entity* ui;
    glm::vec3 _objectColor;
    gr::TransformComponent* p_transform;
};