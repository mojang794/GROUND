#pragma once


namespace engine
{
	class VAO
	{
	public: unsigned int ID;

	public:
		VAO();

		void LinkAttribute(unsigned int index, int size, unsigned int type, int normalized, int stride, const void* pointer);

		void Bind();
		void UnBind();
		
		void Delete();
	};
}

