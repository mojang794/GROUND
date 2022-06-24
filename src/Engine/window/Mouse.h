#pragma once

#include "Window.h"
#include <glm/glm.hpp>

namespace gr
{
    class Mouse
    {
    public:
        enum CursorVisibility
        {
            HIDE,
            SHOW
        };

        enum MouseButton
        {
            LEFT,
            RIGHT,
            MIDDLE
        };

    public:
        static glm::vec2 getPosition(Window* window);
        static bool IsMouseButtonPressed(Window* window, MouseButton b);
        static void setCursorVisibility(Window* window, CursorVisibility v);

    private:
        static double lastX, lastY; 
    };
}