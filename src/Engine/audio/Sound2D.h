#pragma once

#include <SFML/Audio.hpp>

namespace gr
{
    class Sound2D
    {
    private:
        sf::Sound sound;
        sf::SoundBuffer buf;

    public:
        Sound2D(std::string filepath);
        ~Sound2D();

        void play();
        void stop();
        void pause();
        void SetLoop(bool loop = false);
        void SetVolume(float volume);

    };
}