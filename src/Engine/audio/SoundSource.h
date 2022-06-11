#pragma once

#include <AL/al.h>

namespace gr
{
    class SoundSource
    {
    public:
        SoundSource();
        ~SoundSource();

        void Play(const ALuint buffer_to_play);

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