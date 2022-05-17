#pragma once
#include <glad/glad.h>

namespace gr
{
    struct DeviceInfoTypes
    {
        const static int VENDOR;
        const static int RENDERER;
        const static int VERSION;
        const static int SHADING_LANGUAGE_VERSION;
    };

    /**
     * @brief Get the Device Info object
     * 
     * @param T is the device value, in OpenGL for example the GL_VENDOR macro return the GPU vendor,
     *          but with the structure DeviceInfoTypes is already defined
     */
    const GLubyte* GetDeviceInfo(const int T);
}