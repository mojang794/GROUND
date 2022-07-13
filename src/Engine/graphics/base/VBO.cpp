#include "VBO.h"
#include "../../GR_cross_definitions.h"

gr::base::VBO::VBO(int size, const void* data)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void gr::base::VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void gr::base::VBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gr::base::VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}
