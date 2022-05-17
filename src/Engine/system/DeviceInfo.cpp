#include "DeviceInfo.h"

namespace gr
{
    const int DeviceInfoTypes::VENDOR = 0x1F00;
    const int DeviceInfoTypes::RENDERER = 0x1F01;
    const int DeviceInfoTypes::VERSION = 0x1F02;
    const int DeviceInfoTypes::SHADING_LANGUAGE_VERSION = 0x8B8C;

    const GLubyte* GetDeviceInfo(const int T)
    {
        const GLubyte* _context = glGetString(T);
        return _context;
    }
}