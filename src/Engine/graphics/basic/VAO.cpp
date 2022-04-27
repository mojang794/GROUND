#include "VAO.h"
#include <glad/glad.h>

engine::VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void engine::VAO::LinkAttribute(unsigned int index, int size, unsigned int type, int normalized, int stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, false, stride, pointer);
	glEnableVertexAttribArray(index);
}

void engine::VAO::Bind()
{
	glBindVertexArray(ID);
}

void engine::VAO::UnBind()
{
	glBindVertexArray(0);
}

void engine::VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
