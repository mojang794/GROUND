#pragma once

namespace gr
{
    /**
     * @brief Basic Window utils class
     * 
     */
    class WinUtils
    {
#ifdef SFML_SFML_WINDOW_HPP
    public:
        static void LockCursor(sf::Window &window)
        {
            int maxX = window.getSize().x;
            int maxY = window.getSize().y;

            int mX = sf::Mouse::getPosition(window).x;
            int mY = sf::Mouse::getPosition(window).y;

            if (mX < 0 || mY < 0 || mX > maxX || mY > maxY)
            {
                if (mX < 0)
                    mX = 0;
                else if (mX > maxX)
                    mX = maxX;

                if (mY < 0)
                    mY = 0;
                else if (mY > maxY)
                    mY = maxY;

                sf::Mouse::setPosition(sf::Vector2i(mX, mY), window);
            }
        }
#endif
    };
}