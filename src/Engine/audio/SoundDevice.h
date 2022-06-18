#pragma once

#include <AL/alc.h>
#include <vector>
#include <string>

namespace gr
{
    /**
     * @brief Class for open the audio device for play an audio
     * 
     */
    class SoundDevice
    {
    public:
        /**
         * @brief This function open an audio device using OpenAL function, basically get the device from the system 
         * 
         * @param device the audio device to open. Set 'nullptr' to get the default device.
         */
        static SoundDevice* OpenDevice(const ALCchar* device);
        static void CloseDevice();

        static std::vector<const ALCchar*> GetDevices();
    
    private:
        SoundDevice(const ALCchar* device);
        ~SoundDevice();

        std::vector<const ALCchar*> _list_devices;
        ALCdevice* p_ALCDevice;
        ALCcontext* p_ALCContext;
        static SoundDevice* snd;
    };
}