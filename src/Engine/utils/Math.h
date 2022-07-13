#pragma once

#include <cmath>
#include <algorithm>

namespace gr
{
    static const double PI = 3.1415926535;
	static const double PI2 = PI / 2;
	static const double PI3 = 3 * PI / 2;
	static const double DR = 0.0174533; // one degree in radians

    class Math
    {
    public:
        static float GetAngleByAtan(float targetX, float targetY, float target2X, float target2Y)
        {
            return atan2(targetY - target2Y, targetX - target2X);
        }

        static float dist(float ax, float bx, float ay, float by)
        {
            return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
        }

        static float clampf(float _value, float _min, float _max)
        {
            return std::max(_min, std::min(_max, _value));
        }

        template<typename T>
        static T Random(T min, T max)
        {
            assert(max > min); 
            T random = ((T) rand()) / (T) RAND_MAX;

            T range = max - min;
            return (random*range) + min;
        }
    };
}