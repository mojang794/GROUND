#include "GameState.h"
#include <GL/GL.h>
#include <Windows.h>
#include "Engine/utils/Utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Engine/system/Vertex.h"
#include "Engine/system/Color.h"
#include "Engine/Components.h"
#include "Engine/graphics/Shapes.h"
#include "Engine/Joypad.hpp"
#include "Engine/system/Collision.h"

engine::Joypad a;
Entity* e;
GLuint FBO, RBO;
engine::Shader* s;

GameState::GameState(GameDataRef data)
    : _data(data)
{
}

void GameState::init()
{
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    s = new engine::Shader("v.vert", "v.frag");
    

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);  

    s->setInt("ut", 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);  
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Frame Buffer not compleated!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  

    

    player = new Player(_data->supported_keys, &_data->manager);
    player->init();
    
    this->test = &_data->manager.addEntity();
    test->addComponent<TransformComponent>(0.0f, 0.0f, 0.0f, glm::vec3(1.0f));
    test->addComponent<Basic3DGeometry>(Basic3DGeometryShapes::CUBE, Basic3DGeometryRotation::Y, "Core/Shading/cubeFrag.frag", "Core/Shading/lightShader.vert");

    e = &_data->manager.addEntity();
    e->addComponent<TransformComponent>(10, -2, 10, glm::vec3(0.03f));
    e->addComponent<ModelComponent>("Core/model/SuperComputer.obj", "Core/GFX/SC_texture.bmp", "Core/Shading/modelFrag.frag", "Core/Shading/lightShader.vert", GL_TEXTURE0);
}

void GameState::update(float deltaTime)
{

    player->update(deltaTime);
    Collision::AABB(player->GetTransform(), test);
}

void GameState::draw()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    test->getComponent<Basic3DGeometry>().SetProjectionView(
        player->GetProjection(
            _data->window.getSize().x,
            _data->window.getSize().y),
        player->GetView()
    );
    player->UpdateDraw();
    test->getComponent<Basic3DGeometry>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );

    e->getComponent<ModelComponent>().SetProjectionView(
        player->GetProjection(
            _data->window.getSize().x,
            _data->window.getSize().y),
        player->GetView()
    );
    e->getComponent<ModelComponent>().SetLightAttribute(
        player->lightColor, player->GetTransform()->position, player->GetTransform()->position, player->GetFront()
    );


    
}

void GameState::AfterDraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void GameState::destroyGL()
{
    delete test;
    delete this->player;
}