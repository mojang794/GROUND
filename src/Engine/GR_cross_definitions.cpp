#include "GR_cross_definitions.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>

namespace gr
{
    void Log(const char* text)
    {
        #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10);
        printf("[LOG] %s \n", text);
        SetConsoleTextAttribute(hConsole, 7);
        #else
        printf("\033[0;34m[LOG] %s \n", text);
        #endif
    }
    
    void LogError(const char* text)
    {
        #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12);
        printf("[ERROR: %d] %s \n", __LINE__, text);
        SetConsoleTextAttribute(hConsole, 7);
        #else
        printf("\031[0;31m[ERROR: %d] %s \n", __LINE__, text);
        #endif
    }
    
    void LogWarning(const char* text)
    {
        #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 14);
        printf("[WARNING: %d] %s \n", __LINE__, text);
        SetConsoleTextAttribute(hConsole, 7);
        #else
        printf("\033[0;33m[WARNING: %d] %s \n", __LINE__, text);
        #endif
    }

    bool InitOpenGL()
    {
        #ifdef _WIN32
        if (!gladLoadGL()) {
            LogError("Cannot load glad!");
            return false;
        }
        #else
        glewExperiment = true;
        GLenum error = glewInit();
        if (error != GLEW_OK) {
            LogError("Cannot load glew!");
            return false;
        }
        #endif

        return true;
    }
}