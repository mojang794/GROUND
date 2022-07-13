#pragma once

#include "Engine/Camera.h"
#include "Engine/ECS.h"
#include "Engine/utils/ConfigParser.h"
#include "Engine/window/Window.h"
#include "Engine/Components.h"
#include <glm/glm.hpp>
#include <map>

class Player
{
public:
    Player(gr::Manager& m, gr::ConfigFile<int> keys);
    ~Player();

    void Init();
    void Update(float deltatime, gr::Window* win);
    void OnCollision(gr::Entity* e);

    glm::mat4 GetProjection(float w, float y) const;
    glm::mat4 GetView() const;
    gr::Camera* GetCamera() const;

    gr::TransformComponent* GetTransform() const;

    glm::vec3 lightColor;
    glm::ivec2 WindowSize;

private:
    gr::Camera* camera;
    gr::ConfigFile<int> _keys;
};