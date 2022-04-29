#pragma once

#include <SFML/Audio.hpp>

namespace gr
{
    class Sound3D
    {
    private:
        sf::Sound sound;
        sf::SoundBuffer buf;

    public:
        Sound3D(std::string filepath, float minDistance, float attenuation);
        ~Sound3D();

        void play();
        void stop();
        void pause();
        void SetLoop(bool loop = false);
        void SetVolume(float volume);
        void SetPosition(sf::Vector3f pos);

    };
}