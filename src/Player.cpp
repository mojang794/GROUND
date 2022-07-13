#include "Player.h"
#include "Definitions.h"
#include "Engine/window/Keyboard.h"
#include "Engine/window/Mouse.h"
#include "Engine/system/Collision.h"
#include "Engine/audio/Listener.h"

Player::Player(gr::Manager& m, gr::ConfigFile<int> keys)
{
    _keys.copy(keys);
}

Player::~Player()
{

}

void Player::Init()
{
    camera = new gr::Camera(glm::vec3(0, 0, 3.f));
    this->lightColor = glm::vec3(1.0);
}

void Player::Update(float deltaTime, gr::Window* window)
{
    if (gr::Keyboard::IsKeyPressed(window, (gr::Keyboard::Key)this->_keys["MOVE_LEFT"])) {
        this->camera->ProcessKeyboard(gr::Camera_Movement::LEFT, 5 * deltaTime);
    }
    if (gr::Keyboard::IsKeyPressed(window, (gr::Keyboard::Key)this->_keys["MOVE_RIGHT"])) {
        this->camera->ProcessKeyboard(gr::Camera_Movement::RIGHT, 5 * deltaTime);
    }
    if (gr::Keyboard::IsKeyPressed(window, (gr::Keyboard::Key)this->_keys["MOVE_UP"])) {
        this->camera->ProcessKeyboard(gr::Camera_Movement::FORWARD, 5 * deltaTime);
    }
    if (gr::Keyboard::IsKeyPressed(window, (gr::Keyboard::Key)this->_keys["MOVE_DOWN"])) {
        this->camera->ProcessKeyboard(gr::Camera_Movement::BACKWARD, 5 * deltaTime);
    }

    if (gr::Keyboard::IsKeyPressed(window, (gr::Keyboard::Key)this->_keys["LOOK_LEFT"])) {
        this->camera->ProcessMouseMovement(-0.5 * _keys["SENSITIVITY"] * 5, 0);
    }
    if (gr::Keyboard::IsKeyPressed(window, (gr::Keyboard::Key)this->_keys["LOOK_RIGHT"])) {
        this->camera->ProcessMouseMovement(0.5 * _keys["SENSITIVITY"] * 5, 0);
    }
#if !defined(_RELEASE)
    if (gr::Keyboard::IsKeyPressed(window, (gr::Keyboard::Key)this->_keys["LOOK_UP"])) {
        this->camera->ProcessMouseMovement(0, 0.5 * _keys["SENSITIVITY"] * 5);
    }
    if (gr::Keyboard::IsKeyPressed(window, (gr::Keyboard::Key)this->_keys["LOOK_DOWN"])) {
        this->camera->ProcessMouseMovement(0, -0.5 * _keys["SENSITIVITY"] * 5);
    }
#endif

    gr::Listener::SetPosition(
        this->camera->Position.x,
        this->camera->Position.y,
        this->camera->Position.z
    );
}

void Player::OnCollision(gr::Entity* e)
{
    if (gr::Collision::AABB(GetTransform(), e)) {
        camera->velocity = 0;
    }
}

glm::mat4 Player::GetProjection(float w, float y) const
{
    return glm::perspective(glm::radians(45.f), w / y, 0.1f, 1000.f);
}

glm::mat4 Player::GetView() const
{
    return camera->GetViewMatrix();
}

gr::Camera* Player::GetCamera() const
{
    return camera;
}

gr::TransformComponent* Player::GetTransform() const
{
    return new gr::TransformComponent(camera->Position.x, camera->Position.y, camera->Position.z, glm::vec3(0.5, 0.5, 0.5));
}