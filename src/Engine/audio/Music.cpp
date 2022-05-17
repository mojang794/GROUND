#include "Music.h"
#include "../GR_cross_definitions.h"

namespace gr
{
    Music::Music(std::string filepath)
    {
        if (!this->sound.openFromFile(filepath)) {
            gr::Log((std::string("Cannot load: ").append(filepath)).c_str());
            throw "Error! cannot load '" + filepath + "'!";
        }
    }
    
    Music::~Music()
    {
        
    }
    
    void Music::play()
    {
        this->sound.play();
    }
    
    void Music::stop()
    {
        this->sound.stop();
    }
    
    void Music::pause()
    {
        this->sound.pause();
    }
    
    void Music::SetLoop(bool loop)
    {
        this->sound.setLoop(loop);
    }
    
    void Music::SetVolume(float volume)
    {
        this->sound.setVolume(volume);
    }
}