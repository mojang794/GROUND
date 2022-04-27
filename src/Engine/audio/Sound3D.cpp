#include "Sound3D.h"


namespace engine
{
    Sound3D::Sound3D(std::string filepath, float minDistance, float attenuation)
    {
        if (!this->buf.loadFromFile(filepath)) {
            printf("Error! cannot load '%s'!\n", filepath.c_str());
            throw "Error! cannot load '" + filepath + "'!";
        }

        this->sound.setBuffer(this->buf);
        this->sound.setAttenuation(attenuation);
        this->sound.setMinDistance(minDistance);
    }
    
    Sound3D::~Sound3D()
    {
        
    }
    
    void Sound3D::play()
    {
        this->sound.play();
    }
    
    void Sound3D::stop()
    {
        this->sound.stop();
    }
    
    void Sound3D::pause()
    {
        this->sound.pause();
    }
    
    void Sound3D::SetLoop(bool loop)
    {
        this->sound.setLoop(loop);
    }
    
    void Sound3D::SetVolume(float volume)
    {
        this->sound.setVolume(volume);
    }
    
    void Sound3D::SetPosition(sf::Vector3f pos)
    {
        this->sound.setPosition(pos);
    }
}