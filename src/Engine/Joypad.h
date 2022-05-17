#pragma once

#include <SFML/Graphics.hpp>

namespace gr
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
             * @brief Second button
             * 
             * Xbox Equivalent: B ||
             * PS4 Equivalent: O
             */
            B = 1,
            /**
             * @brief Third button
             * 
             * Xbox Equivalent: X ||
             * PS4 Equivalent: []
             */
            X = 2,
            /**
             * @brief Fourth button
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
        // Joypad constructor
        Joypad();

        /**
         * @brief Check if a joypad is connected
         * 
         * @param joypadPlayerNum The player joypad ID, (starts from 0)
         */
        bool ifConnected(unsigned int joypadPlayerNum);
        /**
         * @brief Check if a button is pressed
         *  
         */
        bool buttonPress(JoypadButtons button);
        /**
         * @brief Check if a Axis is moved (Axis == value)
         *  
         */
        bool isAxisEqualTo(sf::Joystick::Axis axis, float value);
        /**
         * @brief Check if a Axis is moved (Axis > value)
         *  
         */
        bool isAxisGreaterTo(sf::Joystick::Axis axis, float value);
        /**
         * @brief Check if a Axis is moved (Axis < value)
         *  
         */
        bool isAxisMinorTo(sf::Joystick::Axis axis, float value);

    private:
        unsigned int _joypadNum;
    };
}