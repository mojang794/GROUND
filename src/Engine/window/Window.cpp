#include "Window.h"

namespace gr
{
    Window::Window(int width, int height, const char* title, WindowSettings settings)
    {
        GR_ASSERT(glfwInit());
        if (settings.Fullscreen)
        {
            _window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
        }
        else
        {
            _window = glfwCreateWindow(width, height, title, NULL, NULL);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.majorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.minorVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, (settings.CoreProfile) ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_ANY_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, settings.antialiasing);
        glfwMakeContextCurrent(_window);
        if (settings.Vsync)
        {
            glfwSwapInterval(0);
        }

        _width = width;
        _height = height;
    }
    
    Window::~Window()
    {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
    
    void Window::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
    
    void Window::Display()
    {
        glfwSwapBuffers(_window);
    }
    
    void Window::PollEvents()
    {
        glfwPollEvents();
        glfwGetWindowSize(_window, &_width, &_height);
    }
    
    void Window::Close()
    {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }
    
    bool Window::IsOpen()
    {
        return !glfwWindowShouldClose(_window);
    }
    
    int Window::GetWidth()
    {
        return _width;
    }
    
    int Window::GetHeight()
    {
        return _height;       
    }
    
    GLFWwindow* Window::GetHandle()
    {
        return _window;
    }
}