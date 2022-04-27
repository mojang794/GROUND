#pragma once

#include "Engine/system/States.hpp"
#include "Game.h"
#include <glm/glm.hpp>
#include "Engine/ECS.h"
#include "Player.h"

class GameState : public engine::States
{
private:
	GameDataRef _data;
	Entity* test;
	Player* player;

public:
	GameState(GameDataRef data);

	void init() override;
	void update(float deltaTime) override;
	void draw() override;	
	void AfterDraw() override;
	void destroyGL() override;
};