#include "GameState.h"
#include <GL/GL.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Engine/graphics/Graphics.h"
#include "Engine/system/Vertex.h"
#include "Engine/system/Color.h"
#include "Engine/Components.h"
#include "Engine/graphics/Shapes.h"
#include "Engine/system/Collision.h"
#include "Definitions.h"
#include <imgui.h>
#include "Engine/audio/SoundSource.h"
#include "Engine/audio/SoundDevice.h"
#include "Engine/audio/SoundBuffer.h"

GameState::GameState(GameDataRef data)
    : _data(data)
{
    
}

void GameState::init()
{
    // gr::SoundDevice::get();
    uint32_t sound = gr::SoundBuffer::get()->addSoundBuffer("Core/audio/P_hurt.wav");
    gr::SoundSource sSource;
    sSource.Play(sound);

    player = new Player(_data->supported_keys, &_data->manager);
    player->init();
    
    this->test = &_data->manager.addEntity();
    test->addComponent<gr::TransformComponent>(0.0f, 0.0f, 0.0f, glm::vec3(1.0f));
    test->addComponent<gr::Basic3DGeometry>(gr::Basic3DGeometryShapes::CUBE, gr::Basic3DGeometryRotation::Y, GetShadingPath("cubeFrag.frag"), GetShadingPath("lightShader.vert"));

    e = &_data->manager.addEntity();
    e->addComponent<gr::TransformComponent>(10, -2, 10, glm::vec3(0.03f));
    e->addComponent<gr::ModelComponent>("Core/model/SuperComputer.obj", "Core/GFX/SC_texture.bmp", GetShadingPath("modelFrag.frag"), GetShadingPath("lightShader.vert"), GL_TEXTURE0);

    h = &_data->manager.addEntity();
    h->addComponent<gr::TransformComponent>(5, 0, 5, glm::vec3(1.0));
    h->addComponent<gr::Basic3DGeometry>(gr::Basic3DGeometryShapes::PYRAMID, gr::Basic3DGeometryRotation::Y, GetShadingPath("piramydFrag.frag"), GetShadingPath("lightShader.vert"));

    b = new gr::Framebuffer(_data->WindowSize.x, _data->WindowSize.y, GetShadingPath("Frame.vert"), GetShadingPath("Frame.frag"));

    _t = new gr::Text(glm::vec2(1024, 768), glm::vec2(10, 10), "Hello World!", "Core/fonts/arial.ttf", 1.0f);
    _t->SetColor(gr::colors::purple);
}

void GameState::update(float deltaTime)
{
    player->update(deltaTime, _data->window);
}

void GameState::draw()
{
    b->Bind();
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _t->Draw();

    test->getComponent<gr::Basic3DGeometry>().SetProjectionView(
        player->GetProjection(_data->WindowSize.x, _data->WindowSize.y),
        player->GetView()
    );
    player->UpdateDraw();
    test->getComponent<gr::Basic3DGeometry>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );

    e->getComponent<gr::ModelComponent>().SetProjectionView(
        player->GetProjection(_data->WindowSize.x, _data->WindowSize.y),
        player->GetView()
    );
    e->getComponent<gr::ModelComponent>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );

    h->getComponent<gr::Basic3DGeometry>().SetProjectionView(
        player->GetProjection(_data->WindowSize.x, _data->WindowSize.y),
        player->GetView()
    );
    h->getComponent<gr::Basic3DGeometry>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );

    h->getComponent<gr::TransformComponent>().angle += 0.05;
}

void GameState::AfterDraw()
{
    b->UnBind();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    b->DrawStorage();
}

void GameState::destroyGL()
{
    delete test;
    delete this->player;
}