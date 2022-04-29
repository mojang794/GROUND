#include "VAO.h"
#include <glad/glad.h>

gr::base::VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void gr::base::VAO::LinkAttribute(unsigned int index, int size, unsigned int type, int normalized, int stride, const void* pointer)
{
	glVertexAttribPointer(index, size, type, false, stride, pointer);
	glEnableVertexAttribArray(index);
}

void gr::base::VAO::Bind()
{
	glBindVertexArray(ID);
}

void gr::base::VAO::UnBind()
{
	glBindVertexArray(0);
}

void gr::base::VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}
