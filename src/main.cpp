// Define macros that have to be defined only one time
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

#include <iostream>
#include <chrono>
#include <thread>
#include "Game.h"
#include <tchar.h>

#ifdef _WIN32
#include <windows.h>

// Windows win main, if we run in windows
int WINAPI wWinMain(
    HINSTANCE hInstance __attribute__((unused)),
    HINSTANCE hPrevInstance __attribute__((unused)), 
    LPWSTR lpCmdLine __attribute__((unused)), 
    int nShowCmd __attribute__((unused))
    )
#else
// common main for any other platforms
int main(int argc __attribute__((unused)), char** argv __attribute__((unused)))
#endif
{
#if defined(_WIN32) && defined(_RELEASE)
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

    try {
        ::Game("GROUND");
    } catch(const char*& e) {
        std::cout << "Error! an error occurred!" << std::endl << "Message: " << e << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return 1;
    }  
    return 0;
}