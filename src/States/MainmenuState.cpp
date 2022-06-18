#include "MainmenuState.h"
#include "GameState.h"
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
        glm::vec2(_data->WindowSize.x / 2 - 150, 700),
        "GROUND", "Core/fonts/StalinistOne-Regular.ttf",
        1
    );
    title->SetColor(gr::colors::yellow);
    start_text = new gr::Text(
        glm::vec2(1024, 768),
        glm::vec2(_data->WindowSize.x / 2 - 210, 10),
        "Press Enter to start", "Core/fonts/inconsolata-Light.ttf",
        1
    );
    start_text->SetColor(gr::colors::white);
    options_text = new gr::Text(
        glm::vec2(1024, 768),
        glm::vec2(_data->WindowSize.x / 2 - 210, 200),
        "Press P to open options", "Core/fonts/inconsolata-Light.ttf",
        1
    );
    options_text->SetColor(gr::colors::white);
    _options = false;

    for (auto e : gr::SoundDevice::GetDevices()) {
        _deviceT.push_back(e);
    }

    _deviceSelected = _data->audio_settings["DEVICE"];
    _globalV = _data->audio_settings["GLOBAL_VOLUME"];
}

void MainmenuState::update(float deltaTime)
{
    if (glfwGetKey(_data->window, GLFW_KEY_ENTER)) {
        _data->audio_settings["GLOBAL_VOLUME"] = (int)_globalV;
        _data->audio_settings["DEVICE"] = (int)_deviceSelected;
        _data->audio_settings.ChangeValues();
        _data->machine.AddState(gr::StatesRef(new GameState(_data)));
    }
}

void MainmenuState::draw()
{
    glClearColor(0.3, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (glfwGetKey(_data->window, GLFW_KEY_P)) {
        _options = true;
    }

    if (_options){
        ImGui::Begin("Options");
        ImGui::ListBox("Audio Device", &_deviceSelected, _deviceT.data(), gr::SoundDevice::GetDevices().size());
        ImGui::Separator();
        ImGui::SliderFloat("Global Volume", &_globalV, 0, 100, std::to_string((int)_globalV).c_str(), 0);
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
