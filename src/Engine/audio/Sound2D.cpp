#include "Sound2D.h"
#include "../GR_cross_definitions.h"

namespace gr
{
    Sound2D::Sound2D(std::string filepath)
    {
        if (!this->buf.loadFromFile(filepath)) {
            gr::LogWarning((std::string("Cannot load: ").append(filepath)).c_str());
        }

        this->sound.setBuffer(this->buf);
    }

    Sound2D::~Sound2D()
    {
        
    }
    
    void Sound2D::play()
    {
        this->sound.play();
    }
    
    void Sound2D::stop()
    {
        this->sound.stop();
    }
    
    void Sound2D::pause()
    {
        this->sound.pause();
    }
    
    void Sound2D::SetLoop(bool loop)
    {
        this->sound.setLoop(loop);
    }
    
    void Sound2D::SetVolume(float volume)
    {
        this->sound.setVolume(volume);
    }
}