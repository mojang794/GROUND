#include "Mouse.h"
#include "../GR_cross_definitions.h"

bool ___f = true;

namespace gr
{
    double Mouse::lastX = 100;
    double Mouse::lastY = 100;

    glm::vec2 Mouse::getPosition(Window* window)
    {
        double ____xpos, ____ypos;
        glfwGetCursorPos(window->GetHandle(), &____xpos, &____ypos);

        return glm::vec2(____xpos, ____ypos);
    }
    
    bool Mouse::IsMouseButtonPressed(Window* window, MouseButton b)
    {
        int state = glfwGetMouseButton(window->GetHandle(), b);
        if (state == GLFW_PRESS) {
            return true;
        }
        return false;
    }
    
    void Mouse::setCursorVisibility(Window* window, CursorVisibility v)
    {
        glfwSetInputMode(window->GetHandle(), GLFW_CURSOR,
            (v == HIDE) ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL
        );
    }
}