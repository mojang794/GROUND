#include "Music.h"

namespace engine
{
    Music::Music(std::string filepath)
    {
        if (!this->sound.openFromFile(filepath)) {
            printf("Error! cannot load '%s'!\n", filepath.c_str());
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