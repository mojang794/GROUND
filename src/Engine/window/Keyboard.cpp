#include "Keyboard.h"
#include <GLFW/glfw3.h>

namespace gr
{
    bool Keyboard::IsKeyPressed(Window* window, Key key)
    {
        if (glfwGetKey(window->GetHandle(), key)) {
            return true;
        }
        return false;
    }
}