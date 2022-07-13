#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include "Game.h"
#include "Engine/graphics/GraphicLoader.h"
#include "States/MainmenuState.h"
#include "Engine/graphics/Shader.h"
#include "Definitions.h"
#include "Engine/system/DeviceInfo.h"
#include "Engine/GR_cross_definitions.h"
#include "Engine/audio/SoundDevice.h"
#include "Engine/window/Keyboard.h"

Game::Game(std::string title)
{
	try
	{
		this->initFile();
		this->initWindow(title);
		gr::InitOpenGL();
		this->initImGui();
		_data->machine.AddState(gr::StatesRef(new MainmenuState(this->_data)));

		debugConsole = false;

		{
			std::stringstream ss;
			ss << "DEVICE INFO:" << std::endl
			   << "  -VENDOR: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::VENDOR) << std::endl
			   << "  -VERSION: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::VERSION) << std::endl
			   << "  -GLSL VERSION: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::SHADING_LANGUAGE_VERSION) << std::endl
			   << "  -RENDERER: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::RENDERER) << std::endl;
			gr::Print("[INFO][GPU]", ss.str().c_str());
		}
		{
			std::stringstream ss;
			ss << "all audio devices: " << std::endl
			   << "-----------------------" << std::endl;
			for (auto e : gr::SoundDevice::GetDevices())
			{
				ss << e << std::endl;
			}
			ss << "-----------------------" << std::endl;
			gr::Print("[INFO][AUDIO]", ss.str().c_str());
		}

		this->run();
	}
	catch (std::exception &e)
	{
		std::cout << "ERROR! something went wrong!" << std::endl
				  << "Error: " << e.what() << std::endl;
		ERROR_MESSAGE("GROUND", (LPCSTR)GR_TO_CSTRING("Error: ", e.what()));
		return;
	}
}

void Game::initFile()
{
	this->_data->graphics_settings.open("settings/Window.ini");
	this->_data->audio_settings.open("settings/Audio.ini");
	this->_data->supported_keys.open("settings/Keyboard.ini");
}

void Game::initWindow(std::string title)
{
	gr::WindowSettings settings;

	settings.antialiasing = _data->graphics_settings["ANTIALIASING"];
	settings.Vsync = _data->graphics_settings["VSYNC"];
	settings.Fullscreen = _data->graphics_settings["FULLSCREEN"];
	settings.Resizable = false;
#if _WIN32
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.CoreProfile = true;
#else
	settings.majorVersion = 2;
	settings.minorVersion = 1;
	settings.CoreProfile = false;
#endif

	_data->window = new gr::Window(
		_data->graphics_settings["WIDTH"], _data->graphics_settings["HEIGHT"],
		title.c_str(), settings
	);
}

void Game::initImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.IniFilename = "settings/ImGui_Settings.ini";
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_data->window->GetHandle(), true);
	ImGui_ImplOpenGL3_Init("#version 120");
}

void Game::run()
{
	try {
		// Predefined Shader
		gr::Shader::CompilePredefinedShader(PREDEFINED_SHADER);
		float m_LastTime = 0, deltatime = 0;
		_data->FPS = 0;
		while (_data->window->IsOpen())
		{
			_data->window->PollEvents();

			this->_data->machine.ProcessChanges();

			// Update scene
			float time = glfwGetTime();
			deltatime = time - m_LastTime;
			m_LastTime = time;

			this->_data->machine.GetActiveState()->update(deltatime);
			_data->manager.refresh();
			_data->manager.update(deltatime);

			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();


			/*----------Additional keybinds-------------*/
			if (gr::Keyboard::IsKeyPressed(_data->window, gr::Keyboard::Key::F5)) {
				debugConsole = true;
			}
			if (gr::Keyboard::IsKeyPressed(_data->window, gr::Keyboard::Key::ESCAPE)) {
				debugConsole = false;
			}
			/*------------------------------------------*/

			if (debugConsole)
			{
				_console.Draw();
			}

			_data->window->Clear();

			// Draw scene
			this->_data->machine.GetActiveState()->draw();
			this->_data->manager.draw();
			this->_data->machine.GetActiveState()->AfterDraw();

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
			_data->window->Display();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		this->_data->manager.destroyGL();
		this->_data->machine.GetActiveState()->destroyGL();
		gr::Shader::DeletePredefinedShader();
		gr::SoundDevice::CloseDevice();

		delete _data->window;
	} catch (std::exception& e) {
		ERROR_MESSAGE("GROUND", (LPCSTR)GR_TO_CSTRING("Error: ", e.what()));
	}
}
