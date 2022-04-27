#include "Player.h"
#include "Engine/Components.h"
#include <SFML/Window.hpp>

Player::Player(std::map<std::string, int> keys, Manager *m)
    : _keys(keys)
{
    this->ui = &m->addEntity();
}

Player::~Player()
{
    delete this->camera;
    delete this->ui;
}

void Player::init()
{
    camera = new engine::Camera(glm::vec3(0, 0, 3.f));
    this->lightColor = glm::vec3(1.0);
    this->_objectColor = glm::vec3(1.0f, 0.0f, 0.0f);

    this->ui->addComponent<TransformComponent>(0.0f, -0.9f, 0.0f, glm::vec3(0.1f));
    this->ui->addComponent<Basic2DGeometry>(Basic2DGeometryShapes::SQUARE, "Core/Shading/PlayerUI.frag", "Core/Shading/PlayerUI.vert");
    this->ui->getComponent<Basic2DGeometry>().SetColor(_objectColor);
}

void Player::update(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys.at("W"))))
    {
        camera->ProcessKeyboard(engine::FORWARD, 5 * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys.at("S"))))
    {
        camera->ProcessKeyboard(engine::BACKWARD, 5 * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys.at("A"))))
    {
        camera->ProcessKeyboard(engine::LEFT, 5 * deltaTime);
    }
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys.at("D"))))
    {
        camera->ProcessKeyboard(engine::RIGHT, 5 * deltaTime);
    }

    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys.at("LEFT_ARROW"))))
        camera->ProcessMouseMovement(-8, 0);
    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)(_keys.at("RIGHT_ARROW"))))
        camera->ProcessMouseMovement(8, 0);

    if (joypad.ifConnected(0))
    {
        /**********************************************************************************************************/
        if (joypad.isAxisMinorTo(sf::Joystick::Axis::Y, -50))
        {
            camera->ProcessKeyboard(engine::FORWARD, 5 * deltaTime);
        }
        if (joypad.isAxisGreaterTo(sf::Joystick::Axis::Y, 50))
        {
            camera->ProcessKeyboard(engine::BACKWARD, 5 * deltaTime);
        }
        if (joypad.isAxisMinorTo(sf::Joystick::Axis::X, -50))
        {
            camera->ProcessKeyboard(engine::LEFT, 5 * deltaTime);
        }
        if (joypad.isAxisGreaterTo(sf::Joystick::Axis::X, 50))
        {
            camera->ProcessKeyboard(engine::RIGHT, 5 * deltaTime);
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
        if (joypad.buttonPress(engine::Joypad::JoypadButtons::A))
        {
            this->lightColor = glm::vec3(1.0);
            this->_objectColor = glm::vec3(1.0f, 0.0f, 0.0f);
        }
        if (joypad.buttonPress(engine::Joypad::JoypadButtons::B))
        {
            this->lightColor = glm::vec3(0.001, 0.001, 0.001);
            this->_objectColor = glm::vec3(0.3, 0.3, 0.3);
        }
        /**********************************************************************************************************/
    }
    this->ui->getComponent<Basic2DGeometry>().SetColor(_objectColor);
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

TransformComponent *Player::GetTransform() const
{
    return new TransformComponent(camera->Position.x, camera->Position.y, camera->Position.z, glm::vec3(0.5, 1.0, 0.5));
}
