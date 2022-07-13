#pragma once

#include "../Engine/system/States.hpp"
#include "../Game.h"
#include "../Engine/ECS.h"
#include "../Engine/graphics/Text.h"
#include "../Engine/audio/SoundDevice.h"

class MainmenuState : public gr::States
{
private:
    GameDataRef _data;
    gr::Text* title, *start_text, *options_text;
    bool _options;
    bool _audio_sett;
    bool _display_sett;
    bool _controls_sett;
    // Audio
    float _globalV = 0;
    int _deviceSelected = 0;
    std::vector<const char*> _deviceT;
    // Display
    bool _vsync, _fullscreen;
    std::vector<const char*> _vidmods;
    int _vidSelected, _vidmodsCount, _antialiasing;
    // Controls
    int _sens_value;

public:
    MainmenuState(GameDataRef data);

    void init() override;
	void update(float deltaTime) override;
	void draw() override;	
	void AfterDraw() override;
	void destroyGL() override;
};
