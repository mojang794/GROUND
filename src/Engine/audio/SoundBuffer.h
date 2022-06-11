#pragma once

#include <AL/al.h>
#include <vector>

namespace gr
{
    class SoundBuffer
    {
    public:
        static SoundBuffer* get();

        ALuint addSoundBuffer(const char* filename);
        bool removeSoundEffect(const ALuint& buffer);

    private:
        SoundBuffer();
        ~SoundBuffer();

        std::vector<ALuint> p_SoundEffectBuffers;
    };
}