#pragma once

namespace engine
{
	class VBO
	{
	public: unsigned int ID;

	public:
		VBO(int size, const void* data);

		void Bind();
		void UnBind();
		void Delete();
	};
}

