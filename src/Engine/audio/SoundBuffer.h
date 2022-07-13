#pragma once

#include <AL/al.h>
#include <vector>

namespace gr
{
    using SoundBuf = ALuint;

    class SoundBuffer
    {
    public:
        /**
         * @brief Singleton static method for getting audio buffer with only one declare
         * 
         */
        static SoundBuffer* get();

        /**
         * @brief Add a buffer to the openal device
         * 
         * @param filename the audio file
         * @return [ ALuint ] the buffer (See SoundSource.h)
         */
        ALuint addSoundBuffer(const char* filename);
        /**
         * @brief Remove the buffer created 
         */
        bool removeSoundEffect(const ALuint& buffer);

    private:
        SoundBuffer();
        ~SoundBuffer();

        std::vector<ALuint> p_SoundEffectBuffers;
    };
}