#ifndef __GR_CROSS_DEFINITIONS_H__
#define __GR_CROSS_DEFINITIONS_H__

#ifdef _WIN32
#include <glad/glad.h>
#include <windows.h>
#elif
#include <GL/glew.h>
#endif

namespace gr
{
    // Log a string
    void Log(const char* text);
    // Log an Error
    void LogError(const char* text);
    // Log a Warning
    void LogWarning(const char* text);

    /**
     * @brief This function init opengl 
     */
    bool InitOpenGL();
}

#endif // __GR_CROSS_DEFINITIONS_H__