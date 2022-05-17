#pragma once

#include <memory>
#include <string>
#include <map>
#include "Engine/system/StateMachine.h"
#include <SFML/Window.hpp>
#include "Engine/ECS.h"

struct GameData
{
	gr::Manager manager;
	gr::StateMachine machine;
	sf::Window window;
	sf::Event event;
	std::map<std::string, int> supported_keys;
	std::map<std::string, int> graphics_settings;
	std::map<std::string, int> audio_settings;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(std::string title);

private:
	GameDataRef _data = std::make_shared<GameData>();
	sf::Time deltatime;
	sf::Time ups = sf::seconds(1.f / 60.f);
	sf::Time accumulator = sf::Time::Zero;
	sf::Clock clock;

	void initFile();

	void run();
};

