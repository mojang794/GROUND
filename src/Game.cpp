#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
		glfwInit();
		if(_data->graphics_settings["FULLSCREEN"] == 1) {
			_data->window = glfwCreateWindow(_data->graphics_settings["WIDTH"], _data->graphics_settings["HEIGHT"],
											title.c_str(), glfwGetPrimaryMonitor(), NULL);
		}
		else {
			_data->window = glfwCreateWindow(_data->graphics_settings["WIDTH"], _data->graphics_settings["HEIGHT"],
											title.c_str(), NULL, NULL);
		}
		#ifdef _WIN32
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		#else
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
		#endif
		glfwWindowHint(GLFW_SAMPLES, _data->graphics_settings["antialiasing"]);
		glfwMakeContextCurrent(_data->window);
		if (_data->graphics_settings["VSYNC"] == 0) {
			glfwSwapInterval(0);
		}

		gr::InitOpenGL();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(_data->window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		_data->machine.AddState(gr::StatesRef(new GameState(this->_data)));

		std::cout << "DEVICE INFO:" << std::endl
              << "  -VENDOR: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::VENDOR) << std::endl
              << "  -VERSION: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::VERSION) << std::endl
              << "  -GLSL VERSION: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::SHADING_LANGUAGE_VERSION) << std::endl
              << "  -RENDERER: " << gr::GetDeviceInfo(gr::DeviceInfoTypes::RENDERER) << std::endl;

		this->run();
	} catch(std::exception& e) {
		std::cout << "ERROR! something went wrong!" << std::endl
				  << "Error: " << e.what() << std::endl;
		return;
	}
}

void Game::initFile()
{
	this->_data->graphics_settings.open("settings/Window.ini");
	this->_data->audio_settings.open("settings/Audio.ini");
	this->_data->supported_keys.open("settings/Keyboard.ini");
}

void Game::run()
{
	try {
		// Predefined Shader
		gr::Shader::CompilePredefinedShader(PREDEFINED_SHADER);

#if defined(_WIN32) && !defined(_RELEASE)
		ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif
		float m_LastTime = 0, deltatime = 0;
		while (!glfwWindowShouldClose(_data->window))
		{
			glfwGetWindowSize(_data->window, &_data->WindowSize.x, &_data->WindowSize.y);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			this->_data->machine.ProcessChanges();
			
			float time = glfwGetTime();
			deltatime = time - m_LastTime;
			m_LastTime = time;
			
			this->_data->machine.GetActiveState()->update(deltatime);
			_data->manager.refresh();
			_data->manager.update(deltatime);

			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			this->_data->machine.GetActiveState()->draw();
			this->_data->manager.draw();
			this->_data->machine.GetActiveState()->AfterDraw();
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(_data->window);
			glfwPollEvents();
		}

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		this->_data->manager.destroyGL();
		this->_data->machine.GetActiveState()->destroyGL();
		gr::Shader::DeletePredefinedShader();
	} catch(std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
