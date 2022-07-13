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

#include "../Engine/utils/Math.h"


GameState::GameState(GameDataRef data)
    : _data(data)
{
    
}

void GameState::init()
{
    gr::SoundDevice::OpenDevice(gr::SoundDevice::GetDevices().at(_data->audio_settings["DEVICE"]));
    gr::SoundBuf sound = gr::SoundBuffer::get()->addSoundBuffer("Core/audio/P_hurt.wav");
    gr::SoundSource* sSource = new gr::SoundSource();
    sSource->SetLoop(true);
    sSource->SetPosition(2.0f, 0.0f, 2.0f);
    sSource->SetVolume(_data->audio_settings["GLOBAL_VOLUME"]);

    player = new Player(_data->manager, _data->supported_keys);
    player->Init();
    
    frame = new gr::Framebuffer(_data->window->GetWidth(), _data->window->GetHeight(), GetShadingPath("Frame.vert"), GetShadingPath("Frame.frag"));

    _t = new gr::Text(glm::vec2(1024, 768), glm::vec2(10, 750), "Hello World!", "Core/fonts/arial.ttf", 0.5f);
    _t->SetColor(gr::Color(0, 1, 0));

    e = &_data->manager.addEntity();
    e->addComponent<gr::TransformComponent>();
    e->addComponent<gr::Basic3DGeometry>(gr::Basic3DGeometryShapes::CUBE, GetShadingPath("Cube.frag"), GetShadingPath("lightShader.vert"));

    plane = &_data->manager.addEntity();
    plane->addComponent<gr::TransformComponent>(0, -2, 0, glm::vec3(2, 2, 2), 90);
    plane->addComponent<gr::Basic2DGeometry>(gr::Basic2DGeometryShapes::PLANE, GetShadingPath("Plane.frag"), GetShadingPath("lightShader.vert"));
    plane->getComponent<gr::Basic2DGeometry>().implement3D = true;

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
    player->Update(deltaTime, _data->window);

    double currentTime = glfwGetTime();
    _data->FPS++;
    if ( currentTime - previousTime >= 1.0 )
    {
        // Display the frame count here any way you want.
        _t->SetText(std::to_string(_data->FPS));

        _data->FPS = 0;
        previousTime = currentTime;
    }

    player->OnCollision(e);

    frame->GetShader()->use();
    frame->GetShader()->setFloat("_clock", deltaTime);
}

void GameState::draw()
{
    this->player->WindowSize = glm::vec2(_data->window->GetWidth(), _data->window->GetHeight());

    frame->Resize(_data->window->GetWidth(), _data->window->GetHeight());

    frame->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    e->getComponent<gr::Basic3DGeometry>().SetProjectionView(
        player->GetProjection(_data->window->GetWidth(), _data->window->GetHeight()),
        player->GetView()
    );
    
    e->getComponent<gr::Basic3DGeometry>().SetLightAttribute(
        player->lightColor, 
        player->GetTransform()->position, 
        player->GetTransform()->position, 
        player->GetCamera()->Front
    );

    plane->getComponent<gr::Basic2DGeometry>().SetViewProjection(
        player->GetProjection(_data->window->GetWidth(), _data->window->GetHeight()),
        player->GetView()
    );
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

    // Draw Transparent things

    _t->Draw();

    frame->UnBind();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    frame->DrawStorage();
}

void GameState::destroyGL()
{
    delete this->player;
    delete this->sky;
    delete frame;
    delete _t;
}