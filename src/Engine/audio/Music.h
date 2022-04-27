#pragma once

#include <SFML/Audio.hpp>

namespace engine
{
    class Music
    {
    private:
        sf::Music sound;

    public:
        Music(std::string filepath);
        ~Music();

        void play();
        void stop();
        void pause();
        void SetLoop(bool loop = false);
        void SetVolume(float volume);

    };
}