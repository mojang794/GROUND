#include "Game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include "Engine/graphics/Graphics.h"
#include "GameState.h"
#include "Engine/graphics/Shader.h"
#include "Definitions.h"
#include "Engine/system/DeviceInfo.h"
#include "Engine/GR_cross_definitions.h"

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
			(_data->graphics_settings.at("FULLSCREEN") == 0 ? 
				sf::VideoMode( _data->graphics_settings.at("WIDTH"), _data->graphics_settings.at("HEIGHT")) :
				sf::VideoMode::getDesktopMode()
			),
			title, 
			(_data->graphics_settings.at("FULLSCREEN") == 0 ? sf::Style::Default : sf::Style::Fullscreen), 
			settings
		);
		this->_data->window.setFramerateLimit(_data->graphics_settings.at("FPS"));
		this->_data->window.setVerticalSyncEnabled(_data->graphics_settings.at("VSYNC"));

		gr::InitOpenGL();

		_data->machine.AddState(gr::StatesRef(new GameState(this->_data)));

		std::cout << "DEVICE INFO:" << std::endl
              << "  -VENDOR: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::VENDOR) << std::endl
              << "  -VERSION: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::VERSION) << std::endl
              << "  -GLSL VERSION: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::SHADING_LANGUAGE_VERSION) << std::endl
              << "  -RENDERER: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::RENDERER) << std::endl;

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
		gr::Shader::CompilePredefinedShader(PREDEFINED_SHADER);

#if defined(_WIN32) && !defined(_RELEASE)
		ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif

		while (_data->window.isOpen())
		{

			this->_data->machine.ProcessChanges();
			
			while(_data->window.pollEvent(_data->event))
			{
				if (_data->event.type == sf::Event::Closed) _data->window.close();
				if (_data->event.type == sf::Event::Resized) glViewport(0, 0, _data->event.size.width, _data->event.size.height);
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
			
			this->_data->machine.GetActiveState()->draw();
			this->_data->manager.draw();
			this->_data->machine.GetActiveState()->AfterDraw();
			
			this->_data->window.display();
		}

		this->_data->manager.destroyGL();
		this->_data->machine.GetActiveState()->destroyGL();
		gr::Shader::DeletePredefinedShader();
	} catch(std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		exit(1);
	}
}
