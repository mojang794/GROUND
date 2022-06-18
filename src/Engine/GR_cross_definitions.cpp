#include "GR_cross_definitions.h"
#include <stdio.h>
#include <iostream>

std::vector<std::string> _log_print_buffer_data, _log_ok_buffer_data, _log_warning_buffer_data, _log_error_buffer_data;

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
        printf("\033[0;34m[OK] %s \n", text);
        #endif

        _log_ok_buffer_data.push_back(GR_TO_CSTRING("[OK] ", text));
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

        _log_error_buffer_data.push_back(GR_TO_CSTRING("[ERROR] ", text));
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
        
        _log_warning_buffer_data.push_back(GR_TO_CSTRING("[WARNING] ", text));
    }
    
    void Print(const char* caption, const char* text)
    {
        std::cout << caption << " " << text << std::endl;
        _log_print_buffer_data.push_back(std::string(caption).append(" ").append(text));
    }
    
    std::vector<std::string> GetLogBuffer(int type)
    {
        if (type == GR_LOG_TYPE_OK)
            return _log_ok_buffer_data;
        if (type == GR_LOG_TYPE_WARNING)
            return _log_warning_buffer_data;
        if (type == GR_LOG_TYPE_ERROR)
            return _log_error_buffer_data;
        if (type == GR_LOG_TYPE_PRINT)
            return _log_print_buffer_data;
        else
            return std::vector<std::string>{}; 
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