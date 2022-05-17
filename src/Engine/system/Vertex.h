#pragma once

#include <glm/glm.hpp>
#include "Color.h"

namespace gr
{
	// basic vertex structure
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texCoords;
		glm::vec3 normal;
	};
}