#include "SoundDevice.h"
#include "../GR_cross_definitions.h"
#include <AL/al.h>
#include <string>
#include <iostream>

namespace gr
{
    SoundDevice* SoundDevice::get()
    {
        static SoundDevice* snd = new SoundDevice();
        return snd;
    }
    
    SoundDevice::SoundDevice()
    {
        p_ALCDevice = alcOpenDevice(nullptr); // default device
        if (!p_ALCDevice) {
            gr::LogError("failed to get sound device!");
        }
        p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);
        if (!p_ALCContext) {
            gr::LogError("failed to set sound context!");
        }

        if (!alcMakeContextCurrent(p_ALCContext)) {
            gr::LogError("failed to make current sound context");
        }

        const ALchar* name = nullptr;
        if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
            name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
        if (!name || alcGetError(p_ALCDevice) != AL_NO_ERROR)
            name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
        
        std::cout << "[AUDIO][OK] Opened " << name << std::endl;
    }
    
    SoundDevice::~SoundDevice()
    {
        if (!alcMakeContextCurrent(nullptr)) {
            gr::LogError("failed to set current context to nullptr!");
        }
        alcDestroyContext(p_ALCContext);
        if (p_ALCContext)
            gr::LogError("failed to unset during close");
        
        if (!alcCloseDevice(p_ALCDevice)) {
            gr::LogError("failed to close sound device");
        }
    }
}