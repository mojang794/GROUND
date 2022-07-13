#include "Listener.h"
#include <AL/al.h>

namespace gr
{
    void Listener::SetPosition(float x, float y, float z)
    {
        alListener3f(AL_POSITION, x, y , z);
    }
    
    void Listener::SetPosition(float position[3])
    {
        alListener3f(AL_POSITION, position[0], position[1], position[2]);
    }
    
    void Listener::SetVelocity(float x, float y, float z)
    {
        alListener3f(AL_VELOCITY, x, y , z);
    }
    
    void Listener::SetVelocity(float velocity[3])
    {
        alListener3f(AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
    }
}