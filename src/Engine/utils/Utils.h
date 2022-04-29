#pragma once

#include <cmath>
#include <stdint.h>
#include <string>
#include <ctime>

namespace gr
{
	namespace dataTypes
	{
		typedef unsigned int uint;
		typedef uint8_t uint8;
		typedef uint16_t uint16;
		typedef uint32_t uint32;
		typedef uint64_t uint64;

		typedef unsigned long ulong;
		typedef unsigned short ushort;
		typedef unsigned char byte;
	}

	namespace utils
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
		};
		
		class Time
		{
		public:
			static std::string GetDateTime()
			{
				time_t rawtime;
				struct tm timeinfo;
				char buffer[80];

				time(&rawtime);
				localtime_s(&timeinfo, &rawtime);
				strftime(buffer, 80, "%d-%m-%Y_%H-%M-%S", &timeinfo);
				return std::string(buffer);
			}

		public:
			static std::string GetDate()
			{
				time_t rawtime;
				struct tm timeinfo;
				char buffer[80];

				time(&rawtime);
				localtime_s(&timeinfo, &rawtime);
				strftime(buffer, 80, "%d-%m-%Y", &timeinfo);
				return std::string(buffer);
			}

		public:
			static std::string GetTime()
			{
				time_t rawtime;
				struct tm timeinfo;
				char buffer[80];

				time(&rawtime);
				localtime_s(&timeinfo, &rawtime);
				strftime(buffer, 80, "%H-%M-%S", &timeinfo);
				return std::string(buffer);
			}
		};

		class WinUtils
		{
		#ifdef SFML_SFML_WINDOW_HPP
		public:
			static void LockCursor(sf::Window& window)
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
}