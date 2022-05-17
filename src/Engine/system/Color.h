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
		float r, g, b;

	public:
		Color(){}

		Color(float R, float G, float B)
		{
			r = R;
			g = G;
			b = B;
		}

		glm::vec3 getColor3V() const
		{
			return glm::vec3(r, g, b);
		}
	};

	const Color purple = Color(143, 0, 255);
	const Color gray = Color(128, 128, 128);
	const Color yellow = Color(1, 1, 0);
	const Color black = Color(0, 0, 0);
	const Color white = Color(255, 255, 255);
}