#include "MainmenuState.h"
#include "GameState.h"
#include "../Engine/window/Keyboard.h"
#include <imgui.h>

MainmenuState::MainmenuState(GameDataRef data)
    : _data(data)
{
    
}

void MainmenuState::init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    title = new gr::Text(
        glm::vec2(1024, 768),
        glm::vec2(_data->window->GetWidth() / 2 - 150, 700),
        "GROUND", "Core/fonts/StalinistOne-Regular.ttf",
        1
    );
    title->SetColor(gr::colors::yellow);
    start_text = new gr::Text(
        glm::vec2(1024, 768),
        glm::vec2(_data->window->GetWidth() / 2 - 210, 10),
        "Press Enter to start", "Core/fonts/inconsolata-Light.ttf",
        1
    );
    start_text->SetColor(gr::colors::white);
    options_text = new gr::Text(
        glm::vec2(1024, 768),
        glm::vec2(_data->window->GetWidth() / 2 - 210, 200),
        "Press P to open options", "Core/fonts/inconsolata-Light.ttf",
        1
    );
    options_text->SetColor(gr::colors::white);
    _options = false;
    _audio_sett = false;
    _display_sett = true;
    _controls_sett = false;

    for (auto e : gr::SoundDevice::GetDevices()) {
        _deviceT.push_back(e);
    }

    // 1024x768 60Hz
    // ...

    const GLFWvidmode* vid = glfwGetVideoModes(glfwGetPrimaryMonitor(), &_vidmodsCount);
    for (unsigned long long i = 0; i < sizeof(vid); i++) {
        std::string ss = std::to_string(vid[i].width) + "x" + std::to_string(vid[i].height) + " " + std::to_string(vid[i].refreshRate) + "Hz";
        _vidmods.push_back(ss.c_str());
    }

    _deviceSelected = _data->audio_settings["DEVICE"];
    _globalV = _data->audio_settings["GLOBAL_VOLUME"];
    _vidSelected = 0;
    _vsync = (bool)_data->graphics_settings["VSYNC"];
    _fullscreen = (bool)_data->graphics_settings["FULLSCREEN"];
    _antialiasing = _data->graphics_settings["ANTIALIASING"];
    _sens_value = _data->supported_keys["SENSITIVITY"];
}

void MainmenuState::update(float deltaTime)
{
    if (gr::Keyboard::IsKeyPressed(_data->window, gr::Keyboard::Key::ENTER)) {
        _data->audio_settings["GLOBAL_VOLUME"] = (int)_globalV;
        _data->audio_settings["DEVICE"] = (int)_deviceSelected;
        _data->audio_settings.ChangeValues();

        _data->supported_keys["SENSITIVITY"] = _sens_value;
        _data->supported_keys.ChangeValues();

        _data->graphics_settings["ANTIALIASING"] = _antialiasing;
        _data->graphics_settings["VSYNC"] = (int)_vsync;
        _data->graphics_settings["FULLSCREEN"] = (int)_fullscreen;
        _data->graphics_settings.ChangeValues();

        _data->machine.AddState(gr::StatesRef(new GameState(_data)));
    }
}

void MainmenuState::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (gr::Keyboard::IsKeyPressed(_data->window, gr::Keyboard::Key::P)) {
        _options = true;
    }

    if (_options){
        ImGui::Begin("Options");
        if (ImGui::Button("Display", ImVec2(100, 20))) {
            _display_sett = true;
            _audio_sett = false;
            _controls_sett = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Audio", ImVec2(100, 20))) {
            _display_sett = false;
            _audio_sett = true;
            _controls_sett = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Controls", ImVec2(100, 20))) {
            _display_sett = false;
            _audio_sett = false;
            _controls_sett = true;
        }
        ImGui::Separator();
        if (_audio_sett) {
            ImGui::ListBox("Audio Device", &_deviceSelected, _deviceT.data(), gr::SoundDevice::GetDevices().size());
            ImGui::Separator();
            ImGui::SliderFloat("Global Volume", &_globalV, 0, 100, std::to_string((int)_globalV).c_str(), 0);
        }
        if (_display_sett) {
            ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Remember! All the display settings need to restart!");
            ImGui::Combo("Resolutions", &_vidSelected, _vidmods.data(), _vidmods.size());
            ImGui::SliderInt("Antialiasing", &_antialiasing, 0, 16, std::to_string(_antialiasing).c_str(), 0);
            ImGui::Checkbox("Vsync", &_vsync);
            ImGui::SameLine();
            ImGui::Checkbox("Fullscreen", &_fullscreen);
        }
        if (_controls_sett) {
            ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "Attention! When VSYNC is disabled, the sensitivity increase.");
            ImGui::SliderInt("Sensivity", &_sens_value, 0, 100, std::to_string(_sens_value).c_str(), 0);
        }

        ImGui::End();
    }

    title->Draw();
    start_text->Draw();
    options_text->Draw();
}

void MainmenuState::AfterDraw()
{
    
}

void MainmenuState::destroyGL()
{
    glDisable(GL_BLEND);
    delete title;
    delete start_text;
    delete options_text;
}
