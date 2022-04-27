#include "VBO.h"
#include <glad/glad.h>

engine::VBO::VBO(int size, const void* data)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void engine::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void engine::VBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void engine::VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
