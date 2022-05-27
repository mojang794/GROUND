#pragma once

#define LINUX_SHADING_PATH   "Core/Shading/linux/"
#define WINDOWS_SHADING_PATH "Core/Shading/windows/"

#ifdef _WIN32
#define GetShadingPath(path) (std::string(WINDOWS_SHADING_PATH).append(path)).c_str()
#else
#define GetShadingPath(path) (std::string(LINUX_SHADING_PATH).append(path)).c_str()
#endif

// Window Definitions
#define APP_ICON
#define WINDOW_SETTINGS     "settings/Window.ini"
#define AUDIO_SETTINGS      "settings/Audio.ini"
#define KEYBOARD_SETTINGS   "settings/Keyboard.ini"

// Core Definitions
#define PREDEFINED_SHADER   GetShadingPath("PredefinedShader.frag")
