#include "SoundSource.h"
namespace gr
{
    SoundSource::SoundSource()
    {
        alGenSources(1, &source);
        alSourcef(source, AL_PITCH, pitch);
        alSourcef(source, AL_GAIN, gain);
        alSource3f(source, AL_POSITION, position[0], position[1], position[2]);
        alSource3f(source, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
        alSourcei(source, AL_LOOPING, loop);
        alSourcei(source, AL_BUFFER, buffer);
    }
    
    SoundSource::~SoundSource()
    {
        alDeleteSources(1, &source);
    }
    
    void SoundSource::Play(const ALuint buffer_to_play)
    {
        if (buffer_to_play != buffer)
        {
            buffer = buffer_to_play;
            alSourcei(source, AL_BUFFER, (ALint)buffer);
        }

        alSourcePlay(source);
    }
    
    void SoundSource::SetVolume(float volume)
    {
        alSourcef(source, AL_GAIN, volume);
    }
    
    void SoundSource::SetLoop(bool loop)
    {
        alSourcei(source, AL_LOOPING, loop);
    }
    
    void SoundSource::SetPosition(float position[3])
    {
        alSource3f(source, AL_POSITION, position[0], position[1], position[2]);
    }
    
    void SoundSource::SetPosition(float x, float y, float z)
    {
        alSource3f(source, AL_POSITION, x, y, z);
    }
}