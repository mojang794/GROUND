#include "Player.h"
#include "Engine/Components.h"
#include <SFML/Window.hpp>
#include "Definitions.h"

Player::Player(gr::ConfigFile<int> keys, gr::Manager *m)
    : _keys(keys)
{
    this->ui = &m->addEntity();
}

Player::~Player()
{
    delete this->camera;
    delete this->ui;
    delete this->p_transform;
}

void Player::init()
{
    camera = new gr::Camera(glm::vec3(0, 0, 3.f));
    this->lightColor = glm::vec3(1.0);
    this->_objectColor = glm::vec3(1.0f, 0.0f, 0.0f);

    this->ui->addComponent<gr::TransformComponent>(0.0f, -0.9f, 0.0f, glm::vec3(0.1f));
    this->ui->addComponent<gr::Basic2DGeometry>(gr::Basic2DGeometryShapes::SQUARE, GetShadingPath("PlayerUI.frag"), GetShadingPath("PlayerUI.vert"));
    this->ui->getComponent<gr::Basic2DGeometry>().SetColor(_objectColor);
    p_transform = new gr::TransformComponent(camera->Position.x, camera->Position.y, camera->Position.z, glm::vec3(0.5, 1.0, 0.5));
}

void Player::update(float deltaTime)
{
    p_transform->position = camera->Position;
    
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys["W"])))
    {
        camera->ProcessKeyboard(gr::FORWARD, 5 * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys["S"])))
    {
        camera->ProcessKeyboard(gr::BACKWARD, 5 * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys["A"])))
    {
        camera->ProcessKeyboard(gr::LEFT, 5 * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys["D"])))
    {
        camera->ProcessKeyboard(gr::RIGHT, 5 * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys["LEFT_ARROW"])))
        camera->ProcessMouseMovement(-8, 0);
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys["RIGHT_ARROW"])))
        camera->ProcessMouseMovement(8, 0);

    if (joypad.ifConnected(0))
    {
        /**********************************************************************************************************/
        if (joypad.isAxisMinorTo(sf::Joystick::Axis::Y, -50))
        {
            camera->ProcessKeyboard(gr::FORWARD, 5 * deltaTime);
        }
        if (joypad.isAxisGreaterTo(sf::Joystick::Axis::Y, 50))
        {
            camera->ProcessKeyboard(gr::BACKWARD, 5 * deltaTime);
        }
        if (joypad.isAxisMinorTo(sf::Joystick::Axis::X, -50))
        {
            camera->ProcessKeyboard(gr::LEFT, 5 * deltaTime);
        }
        if (joypad.isAxisGreaterTo(sf::Joystick::Axis::X, 50))
        {
            camera->ProcessKeyboard(gr::RIGHT, 5 * deltaTime);
        }

        if (joypad.isAxisMinorTo(sf::Joystick::Axis::U, -50))
        {
            camera->ProcessMouseMovement(-5, 0);
        }
        if (joypad.isAxisGreaterTo(sf::Joystick::Axis::U, 50))
        {
            camera->ProcessMouseMovement(5, 0);
        }
        /**********************************************************************************************************/
    }
}

void Player::UpdateDraw()
{
    if (joypad.ifConnected(0))
    {
        /**********************************************************************************************************/
        if (joypad.buttonPress(gr::Joypad::JoypadButtons::A))
        {
            this->lightColor = glm::vec3(1.0);
            this->_objectColor = glm::vec3(1.0f, 0.0f, 0.0f);
        }
        if (joypad.buttonPress(gr::Joypad::JoypadButtons::B))
        {
            this->lightColor = glm::vec3(0.001, 0.001, 0.001);
            this->_objectColor = glm::vec3(0.3, 0.3, 0.3);
        }
        /**********************************************************************************************************/
    }
    this->ui->getComponent<gr::Basic2DGeometry>().SetColor(_objectColor);
}

glm::mat4 Player::GetProjection(float w, float h) const
{
    return glm::perspective(
        glm::radians(camera->Zoom),
        (float)w / (float)h, 0.1f, 100.0f);
}

glm::mat4 Player::GetView() const
{
    return camera->GetViewMatrix();
}

glm::vec3 Player::GetFront() const
{
    return camera->Front;
}

gr::TransformComponent *Player::GetTransform() const
{
    return p_transform;
}
