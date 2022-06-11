#include "GR_cross_definitions.h"
#include <stdio.h>

namespace gr
{
    void Log(const char* text)
    {
        #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10);
        printf("[OK] %s \n", text);
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
        printf("[ERROR] %s \n", text);
        SetConsoleTextAttribute(hConsole, 7);
        #else
        printf("\031[0;31m[ERROR] %s \n", text);
        #endif
    }
    
    void LogWarning(const char* text)
    {
        #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 14);
        printf("[WARNING] %s \n", text);
        SetConsoleTextAttribute(hConsole, 7);
        #else
        printf("\033[0;33m[WARNING] %s \n", text);
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