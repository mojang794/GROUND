#include "SoundDevice.h"
#include "../GR_cross_definitions.h"
#include <AL/al.h>
#include <iostream>

namespace gr
{
    SoundDevice *SoundDevice::snd = nullptr;

    SoundDevice *SoundDevice::OpenDevice(const ALCchar* device)
    {
        snd = new SoundDevice(device);
        return snd;
    }
    
    void SoundDevice::CloseDevice()
    {
        delete snd;
    }
    
    std::vector<const ALCchar*> SoundDevice::GetDevices()
    {
        std::vector<const ALCchar*> _devices;
        const ALCchar *device = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER), 
                      *next = alcGetString(NULL, ALC_ALL_DEVICES_SPECIFIER) + 1;
        size_t len = 0;
        while (device && *device != '\0' && next && *next != '\0') {
                _devices.push_back(device);
                len = strlen(device);
                device += (len + 1);
                next += (len + 2);
        }
        return _devices;
    }

    SoundDevice::SoundDevice(const ALCchar* device)
    {
        _list_devices = GetDevices();

        p_ALCDevice = alcOpenDevice(device);
        if (!p_ALCDevice)
        {
            gr::LogError("failed to get sound device!");
        }
        p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);
        if (!p_ALCContext)
        {
            gr::LogError("failed to set sound context!");
        }

        if (!alcMakeContextCurrent(p_ALCContext))
        {
            gr::LogError("failed to make current sound context");
        }

        const ALchar *name = nullptr;
        if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
            name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
        if (!name || alcGetError(p_ALCDevice) != AL_NO_ERROR)
            name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);

        gr::Print("[AUDIO][OK]", GR_TO_CSTRING("Opened ", name));
    }

    SoundDevice::~SoundDevice()
    {
        if (!alcMakeContextCurrent(nullptr))
        {
            gr::LogError("failed to set current context to nullptr!");
        }
        alcDestroyContext(p_ALCContext);
        if (!p_ALCContext)
            gr::LogError("failed to unset during close");

        if (!alcCloseDevice(p_ALCDevice))
        {
            gr::LogError("failed to close sound device");
        }
        else
        {
            gr::Print("[AUDIO][OK]", "Audio device closed");
        }
    }
}