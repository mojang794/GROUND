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
    float _globalV = 0;
    int _deviceSelected = 0;
    std::vector<const char*> _deviceT;
    bool _options;

public:
    MainmenuState(GameDataRef data);

    void init() override;
	void update(float deltaTime) override;
	void draw() override;	
	void AfterDraw() override;
	void destroyGL() override;
};
