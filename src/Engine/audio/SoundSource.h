#pragma once

#include <AL/al.h>

namespace gr
{
    /**
     * @brief Base class for play a sound
     * 
     */
    class SoundSource
    {
    public:
        SoundSource();
        ~SoundSource();

        /**
         * @brief Play a sound
         * 
         * @param buffer_to_play the audio buffer (See SoundBuffer.h for loading)
         */
        void Play(const ALuint buffer_to_play);
        void SetVolume(float volume);
        void SetLoop(bool loop);
        
        void SetPosition(float position[3]);
        void SetPosition(float x, float y, float z);

    private:
        ALuint source;
        float pitch = 1.0f;
        float gain = 1.0f;
        float position[3] = {0, 0, 0};
        float velocity[3] = {0, 0, 0};
        bool loop = false;
        ALuint buffer = 0;
    };
}