#pragma once

#include "../GR_cross_definitions.h"
#include <GLFW/glfw3.h>

namespace gr
{   
    struct WindowSettings
    {
        short antialiasing;
        short majorVersion, minorVersion;
        bool CoreProfile, Vsync, Fullscreen, Resizable;
    };

    class Window
    {
    public:
        Window(int width, int height, const char* title, WindowSettings settings);
        ~Window();

        void Clear();
        void Display();
        void PollEvents();
        void Close();
        bool IsOpen();

        int GetWidth();
        int GetHeight();
        GLFWwindow* GetHandle();
    
    private:
        GLFWwindow* _window;
        int _width, _height;
    };
}