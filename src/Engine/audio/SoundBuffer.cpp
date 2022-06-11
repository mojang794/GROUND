#include "SoundBuffer.h"
#include <AL/alext.h>
#include "../GR_cross_definitions.h"
#include <string>
#include <fstream>
#include <memory>
#include <iostream>
#include <cstring>
#include <sndfile.h>

namespace gr
{
    SoundBuffer *SoundBuffer::get()
    {
        static SoundBuffer *sndbuf = new SoundBuffer();
        return sndbuf;
    }

    ALuint SoundBuffer::addSoundBuffer(const char *filename)
    {
        ALenum err, format;
        ALuint buffer;
        short *membuf;
        ALsizei num_bytes;
        SNDFILE* sndfile;
        SF_INFO sfinfo;
        sf_count_t num_frames;

        // Read and decode format
        sndfile = sf_open(filename, SFM_READ, &sfinfo);
        if (!sndfile) {
            gr::LogWarning(GR_TO_CSTRING("Cannot open: ", filename));
            return 0;
        }
        if (sfinfo.frames < 1 || sfinfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels) {
            gr::LogWarning(GR_TO_CSTRING("Bad sample count in: ", filename));
            sf_close(sndfile);
            return 0;
        }

        format = AL_NONE;
        if (sfinfo.channels == 1)
            format = AL_FORMAT_MONO16;
        else if (sfinfo.channels == 2)
            format = AL_FORMAT_STEREO16;
        else if (sfinfo.channels == 3)
        {
            if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
                format = AL_FORMAT_BFORMAT2D_16;
            }
        }
        else if (sfinfo.channels == 4)
        {
            if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
                format = AL_FORMAT_BFORMAT3D_16;
            }
        }
        if (!format)
        {
            gr::LogError("Unsupported channels!");
            return 0;
        }

        // Decode audio
        membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

        num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
        if (num_frames < 1)
        {
            free(membuf);
            sf_close(sndfile);
            gr::LogError(GR_TO_CSTRING("Failed to read samples in: ", filename));
            return 0;
        }
        num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

        // buffer the audio data
        buffer = 0;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

        free(membuf);
        sf_close(sndfile);

        // Check openal errors
        err = alGetError();
        if (err != AL_NO_ERROR)
        {
            gr::LogError(GR_TO_CSTRING("OpenAL error: ", alGetString(err)));
            if (buffer && alIsBuffer(buffer)) {
                alDeleteBuffers(1, &buffer);
            }
            return 0;
        }

        p_SoundEffectBuffers.push_back(buffer);

        return buffer;
    }

    bool SoundBuffer::removeSoundEffect(const ALuint &buffer)
    {
        auto it = p_SoundEffectBuffers.begin();
        while (it != p_SoundEffectBuffers.end())
        {
            if (*it == buffer)
            {
                alDeleteBuffers(1, &*it);

                it = p_SoundEffectBuffers.erase(it);
                
                return true;
            }
            else {
                ++it;
            }
        }
        return false; // couldn't remove any
    }

    SoundBuffer::SoundBuffer()
    {
        p_SoundEffectBuffers.clear();
    }

    SoundBuffer::~SoundBuffer()
    {
        alDeleteBuffers(p_SoundEffectBuffers.size(), p_SoundEffectBuffers.data());

        p_SoundEffectBuffers.clear();
    }
}