#include "Player.h"
#include "Engine/Components.h"
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

void Player::update(float deltaTime, GLFWwindow* window)
{
    p_transform->position = camera->Position;
    
    if (glfwGetKey(window, this->_keys["A"])) {
        this->camera->ProcessKeyboard(gr::Camera_Movement::LEFT, 5 * deltaTime);
    }
    if (glfwGetKey(window, this->_keys["D"])) {
        this->camera->ProcessKeyboard(gr::Camera_Movement::RIGHT, 5 * deltaTime);
    }
    if (glfwGetKey(window, this->_keys["W"])) {
        this->camera->ProcessKeyboard(gr::Camera_Movement::FORWARD, 5 * deltaTime);
    }
    if (glfwGetKey(window, this->_keys["S"])) {
        this->camera->ProcessKeyboard(gr::Camera_Movement::BACKWARD, 5 * deltaTime);
    }

    if (glfwGetKey(window, this->_keys["LEFT_ARROW"])) {
        this->camera->ProcessMouseMovement(-0.5, 0);
    }
    if (glfwGetKey(window, this->_keys["RIGHT_ARROW"])) {
        this->camera->ProcessMouseMovement(0.5, 0);
    }
}

void Player::UpdateDraw()
{
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
