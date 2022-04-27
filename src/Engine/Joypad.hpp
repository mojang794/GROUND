#pragma once

#include <SFML/Graphics.hpp>

namespace engine
{
    class Joypad
    {
    public:
        enum JoypadButtons
        {
            /**
             * @brief First button
             * 
             * Xbox Equivalent: A ||
             * PS4 Equivalent: X
             */
            A = 0,
            /**
             * @brief First button
             * 
             * Xbox Equivalent: B ||
             * PS4 Equivalent: O
             */
            B = 1,
            /**
             * @brief First button
             * 
             * Xbox Equivalent: X ||
             * PS4 Equivalent: []
             */
            X = 2,
            /**
             * @brief First button
             * 
             *Xbox Equivalent: Y ||
             *PS4 Equivalent: Δ
             */
            Y = 3,
            L1 = 4,
            R1 = 5,
            BACK = 8,
            START = 9,
            LEFT_THUMB = 6,
            RIGHT_THUMB = 7
        };

    public:
        Joypad();

        bool ifConnected(unsigned int joypadPlayerNum);
        bool buttonPress(JoypadButtons button);
        bool isAxisEqualTo(sf::Joystick::Axis axis, float value);
        bool isAxisGreaterTo(sf::Joystick::Axis axis, float value);
        bool isAxisMinorTo(sf::Joystick::Axis axis, float value);

    private:
        unsigned int _joypadNum;
    };
}