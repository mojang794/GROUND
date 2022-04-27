#include "Game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include "Engine/utils/Utils.h"
#include "Engine/graphics/Graphics.h"
#include "GameState.h"
#include "Engine/graphics/Shader.h"
#include "Definitions.h"

Game::Game(std::string title)
{
	try {
		this->initFile();

		sf::ContextSettings settings;
		settings.antialiasingLevel = _data->graphics_settings.at("antialiasing");
		settings.majorVersion = 3;
		settings.minorVersion = 3;
		settings.depthBits = 24;
		settings.stencilBits = 8;

		this->_data->window.create(
			sf::VideoMode(_data->graphics_settings.at("WIDTH"), _data->graphics_settings.at("HEIGHT")),
			title, sf::Style::Default, settings
		);
		this->_data->window.setFramerateLimit(_data->graphics_settings.at("FPS"));
		this->_data->window.setVerticalSyncEnabled(_data->graphics_settings.at("VSYNC"));

		if (!gladLoadGL()) {
			std::cout << "Error! cannot load GLAD!" << std::endl;
			throw "Error! cannot load GLAD!";
		}

		_data->machine.AddState(engine::StatesRef(new GameState(this->_data)));

		this->run();
	} catch(std::exception& e) {
		std::cout << "ERROR! something have goes wrong!" << std::endl
				  << "Error: " << e.what() << std::endl;
		sf::sleep(sf::seconds(5.f));
		exit(1);
	}
}

void Game::initFile()
{
	{
		std::ifstream file(WINDOW_SETTINGS);
		std::string key = "";
		char symbol;
		int value;
		if (file.is_open()) {
			while (file >> key >> symbol >> value)
			{
				if (symbol == '=')
				{
					this->_data->graphics_settings[key] = value;
				}
			}
		}

		file.close();
	}

	{
		std::ifstream file(AUDIO_SETTINGS);
		std::string key = "";
		char symbol;
		int value;
		while (file >> key >> symbol >> value)
		{
			if (symbol == '=')
			{
				this->_data->audio_settings[key] = value;
			}
		}
		file.close();
	}

	{
		std::ifstream file(KEYBOARD_SETTINGS);
		std::string key = "";
		char symbol;
		int value;
		while (file >> key >> symbol >> value)
		{
			if (symbol == '=')
			{
				this->_data->supported_keys[key] = value;
			}
		}
		file.close();
	}
}

void Game::run()
{
	try {
		glEnable(GL_DEPTH_TEST);

		// Predefined Shader
		engine::Shader::CompilePredefinedShader(PREDEFINED_SHADER);


		while (_data->window.isOpen())
		{	
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			this->_data->machine.ProcessChanges();
			
			sf::Event ev;
			while(_data->window.pollEvent(ev))
			{
				if (ev.type == sf::Event::Closed) _data->window.close();
				if (ev.type == sf::Event::Resized) glViewport(0, 0, ev.size.width, ev.size.height);
			}

			this->deltatime = this->clock.restart();
			this->accumulator += deltatime;
			while (this->accumulator >= this->ups)
			{
				this->accumulator -= this->ups;
				if (_data->window.hasFocus())
				{
					this->_data->machine.GetActiveState()->update(this->ups.asSeconds());
					_data->manager.refresh();
					_data->manager.update(this->ups.asSeconds());
				}
			}
			
			this->_data->manager.draw();
			this->_data->machine.GetActiveState()->draw();
			this->_data->machine.GetActiveState()->AfterDraw();
			
			this->_data->window.display();
			

		}

		this->_data->manager.destroyGL();
		this->_data->machine.GetActiveState()->destroyGL();
		engine::Shader::DeletePredefinedShader();
	} catch(std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		exit(1);
	}
}
