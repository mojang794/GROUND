#include "Joypad.hpp"

using namespace gr;

Joypad::Joypad()
    : _joypadNum(0)
{
    
}

bool Joypad::ifConnected(unsigned int joypadPlayerNum) {
    if (!sf::Joystick::isConnected(joypadPlayerNum)){
        this->_joypadNum = joypadPlayerNum;
        return false;
    }
    return true;
}

bool Joypad::buttonPress(JoypadButtons button) {
    if (sf::Joystick::isButtonPressed(this->_joypadNum, button)){
        return true;
    }
    return false;
}

bool engine::Joypad::isAxisEqualTo(sf::Joystick::Axis axis, float value)
{
    if (sf::Joystick::getAxisPosition(this->_joypadNum, axis) == value) {
        return true;
    }
    return false;
}

bool engine::Joypad::isAxisGreaterTo(sf::Joystick::Axis axis, float value)
{
    if (sf::Joystick::getAxisPosition(this->_joypadNum, axis) > value) {
        return true;
    }
    return false;
}

bool engine::Joypad::isAxisMinorTo(sf::Joystick::Axis axis, float value)
{
    if (sf::Joystick::getAxisPosition(this->_joypadNum, axis) < value) {
        return true;
    }
    return false;
}


