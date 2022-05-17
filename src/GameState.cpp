#include "GameState.h"
#include <GL/GL.h>
#include <Windows.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Engine/system/Vertex.h"
#include "Engine/system/Color.h"
#include "Engine/Components.h"
#include "Engine/graphics/Shapes.h"
#include "Engine/system/Collision.h"
#include "Engine/graphics/Framebuffer.h"

gr::Entity* e;
gr::Framebuffer* b;

GameState::GameState(GameDataRef data)
    : _data(data)
{
    
}

void GameState::init()
{
    player = new Player(_data->supported_keys, &_data->manager);
    player->init();
    
    this->test = &_data->manager.addEntity();
    test->addComponent<gr::TransformComponent>(0.0f, 0.0f, 0.0f, glm::vec3(1.0f));
    test->addComponent<gr::Basic3DGeometry>(gr::Basic3DGeometryShapes::CUBE, gr::Basic3DGeometryRotation::Y, "Core/Shading/cubeFrag.frag", "Core/Shading/lightShader.vert");

    e = &_data->manager.addEntity();
    e->addComponent<gr::TransformComponent>(10, -2, 10, glm::vec3(0.03f));
    e->addComponent<gr::ModelComponent>("Core/model/SuperComputer.obj", "Core/GFX/SC_texture.bmp", "Core/Shading/modelFrag.frag", "Core/Shading/lightShader.vert", GL_TEXTURE0);

    b = new gr::Framebuffer(_data->window.getSize().x, _data->window.getSize().y, "Core/Shading/Frame.vert", "Core/Shading/Frame.frag");
}

void GameState::update(float deltaTime)
{
    player->update(deltaTime);
}

void GameState::draw()
{
    b->Bind();
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    test->getComponent<gr::Basic3DGeometry>().SetProjectionView(
        player->GetProjection(
            _data->window.getSize().x,
            _data->window.getSize().y),
        player->GetView()
    );
    player->UpdateDraw();
    test->getComponent<gr::Basic3DGeometry>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );

    e->getComponent<gr::ModelComponent>().SetProjectionView(
        player->GetProjection(
            _data->window.getSize().x,
            _data->window.getSize().y),
        player->GetView()
    );
    e->getComponent<gr::ModelComponent>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );
}

void GameState::AfterDraw()
{
    b->UnBind();
    
    glDisable(GL_DEPTH_TEST);
    b->DrawStorage();
}

void GameState::destroyGL()
{
    delete test;
    delete this->player;
}