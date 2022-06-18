#pragma once

#include "../Engine/system/States.hpp"
#include "../Game.h"
#include <glm/glm.hpp>
#include "../Engine/ECS.h"
#include "../Player.h"
#include "../Engine/graphics/Framebuffer.h"
#include "../Engine/graphics/Text.h"
#include "../Engine/graphics/Skybox.h"

class GameState : public gr::States
{
private:
	GameDataRef _data;
	gr::Entity* test;
	Player* player;
	gr::Entity* e, *h;
	gr::Framebuffer* b;
	gr::Text* _t;
	gr::SkyBox* sky;

public:
	GameState(GameDataRef data);

	void init() override;
	void update(float deltaTime) override;
	void draw() override;	
	void AfterDraw() override;
	void destroyGL() override;
};