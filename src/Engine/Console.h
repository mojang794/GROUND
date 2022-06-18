#pragma once

namespace gr
{
    /**
     * @brief Base class for a console log gui with ImGui
     * 
     */
    class Console
    {
    public:
        Console();
        ~Console();

        void Draw();    
    private:
        bool _w, _e, _p, _k;
    };
}