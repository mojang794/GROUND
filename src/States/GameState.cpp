#include "GameState.h"
#include <GL/GL.h>
#include "../Engine/graphics/GraphicLoader.h"
#include "../Engine/system/Vertex.h"
#include "../Engine/system/Color.h"
#include "../Engine/Components.h"
#include "../Engine/graphics/Shapes.h"
#include "../Engine/system/Collision.h"
#include "../Definitions.h"
#include "../Engine/audio/SoundSource.h"
#include "../Engine/audio/SoundBuffer.h"
#include "../Engine/audio/SoundDevice.h"
#include "../Engine/window/Mouse.h"

GameState::GameState(GameDataRef data)
    : _data(data)
{
    
}

void GameState::init()
{
    gr::SoundDevice::OpenDevice(gr::SoundDevice::GetDevices().at(_data->audio_settings["DEVICE"]));
    uint32_t sound = gr::SoundBuffer::get()->addSoundBuffer("Core/audio/P_hurt.wav");
    gr::SoundSource* sSource = new gr::SoundSource();

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

    playerModel = &_data->manager.addEntity();
    playerModel->addComponent<gr::TransformComponent>(-5, 0, -5);
    playerModel->addComponent<gr::ModelComponent>("Core/model/Player2.obj", "Core/GFX/PlayerTexture.png", GetShadingPath("modelFrag.frag"), GetShadingPath("lightShader.vert"), GL_TEXTURE0);

    b = new gr::Framebuffer(_data->window->GetWidth(), _data->window->GetHeight(), GetShadingPath("Frame.vert"), GetShadingPath("Frame.frag"));

    _t = new gr::Text(glm::vec2(1024, 768), glm::vec2(10, 750), "Hello World!", "Core/fonts/arial.ttf", 0.5f);
    _t->SetColor(gr::Color(0, 1, 0));

    std::vector<std::string> skyFiles = 
    {
        "Core/GFX/skybox/right.jpg",
        "Core/GFX/skybox/left.jpg",
        "Core/GFX/skybox/top.jpg",
        "Core/GFX/skybox/bottom.jpg",
        "Core/GFX/skybox/front.jpg",
        "Core/GFX/skybox/back.jpg",
    };

    sky = new gr::SkyBox(GetShadingPath("SkyBox.vert"), GetShadingPath("SkyBox.frag"), skyFiles);


    gr::Log("Loaded everything!");
    sSource->Play(sound);

    gr::Mouse::setCursorVisibility(_data->window, gr::Mouse::SHOW);
}

double previousTime = glfwGetTime();

void GameState::update(float deltaTime)
{
    player->update(deltaTime, _data->window);

    double currentTime = glfwGetTime();
    _data->FPS++;
    if ( currentTime - previousTime >= 1.0 )
    {
        // Display the frame count here any way you want.
        _t->SetText(std::to_string(_data->FPS));

        _data->FPS = 0;
        previousTime = currentTime;
    }
}

void GameState::draw()
{
    this->player->WindowSize = glm::vec2(_data->window->GetWidth(), _data->window->GetHeight());

    b->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _t->Draw();

    player->UpdateDraw();
    
    test->getComponent<gr::Basic3DGeometry>().SetProjectionView(
        player->GetProjection(_data->window->GetWidth(), _data->window->GetHeight()),
        player->GetView()
    );
    
    test->getComponent<gr::Basic3DGeometry>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );

    e->getComponent<gr::ModelComponent>().SetProjectionView(
        player->GetProjection(_data->window->GetWidth(), _data->window->GetHeight()),
        player->GetView()
    );
    e->getComponent<gr::ModelComponent>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );

    playerModel->getComponent<gr::ModelComponent>().SetProjectionView(
        player->GetProjection(_data->window->GetWidth(), _data->window->GetHeight()),
        player->GetView()
    );
    playerModel->getComponent<gr::ModelComponent>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );

    h->getComponent<gr::Basic3DGeometry>().SetProjectionView(
        player->GetProjection(_data->window->GetWidth(), _data->window->GetHeight()),
        player->GetView()
    );
    h->getComponent<gr::Basic3DGeometry>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );

    h->getComponent<gr::TransformComponent>().angle += 0.05;
}

void GameState::AfterDraw()
{
    sky->SetVP(
        player->GetProjection(_data->window->GetWidth(), _data->window->GetHeight()),
        player->GetView()
    );
    
    glDepthFunc(GL_LEQUAL);
    sky->Draw();
    glDepthFunc(GL_LESS);

    b->UnBind();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    b->DrawStorage();
}

void GameState::destroyGL()
{
    delete test;
    delete this->player;
    delete this->sky;
    delete e;
    delete h;
    delete b;
    delete _t;
    delete playerModel;
}