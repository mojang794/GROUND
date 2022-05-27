#pragma once

#include <glm/glm.hpp>

namespace gr {
	/**
	 * @brief Basic Color class
	 * 
	 */
	class Color
	{
	public:
		float r, g, b, a;

	public:
		Color(){}

		Color(float R, float G, float B)
		{
			r = R;
			g = G;
			b = B;
		}

		Color(float R, float G, float B, float A)
		{
			r = R;
			g = G;
			b = B;
			a = A;
		}

		glm::vec3 getColor3V() const
		{
			return glm::vec3(r, g, b);
		}

		glm::vec4 getColor4V() const
		{
			return glm::vec4(r, g, b, a);
		}
	};

	namespace colors {
		const static Color purple = Color(143, 0, 255);
		const static Color gray = Color(128, 128, 128);
		const static Color yellow = Color(1, 1, 0);
		const static Color black = Color(0, 0, 0);
		const static Color white = Color(255, 255, 255);
	}
}