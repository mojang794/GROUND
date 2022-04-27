// Define macros that have to be defined only one time
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <chrono>
#include <thread>
#include "Game.h"
#include <windows.h>
#include <tchar.h>

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    try {
        ::Game("GROUND");
    } catch(std::exception& e) {
        std::cout << "Error! an error occurred!" << std::endl << "Line: " << __LINE__ << " Message: " << e.what() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        return 1;
    }
    
    return 0;
}