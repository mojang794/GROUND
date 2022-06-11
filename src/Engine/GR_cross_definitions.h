#ifndef __GR_CROSS_DEFINITIONS_H__
#define __GR_CROSS_DEFINITIONS_H__

#include <assert.h>

#ifdef _WIN32
#include <glad/glad.h>
#include <windows.h>
#elif
#include <GL/glew.h>
#endif

#define GR_TO_CSTRING(x_cxx_string, y_arg) (std::string(x_cxx_string).append(y_arg)).c_str()

#define GR_ASSERT(condition) assert(condition)

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