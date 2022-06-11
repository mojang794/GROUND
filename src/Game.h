#pragma once

#include <memory>
#include <string>
#include <map>
#include "Engine/system/StateMachine.h"
#include "Engine/utils/ConfigParser.h"
#include "Engine/ECS.h"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct GameData
{
	GLFWwindow* window;
	glm::ivec2 WindowSize;
	gr::Manager manager;
	gr::StateMachine machine;
	gr::ConfigFile<int> supported_keys;
	gr::ConfigFile<int> graphics_settings;
	gr::ConfigFile<int> audio_settings;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
	Game(std::string title);

private:
	GameDataRef _data = std::make_shared<GameData>();

	void initFile();

	void run();
};

