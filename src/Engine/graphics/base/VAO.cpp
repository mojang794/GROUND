#include "VAO.h"
#include "../../GR_cross_definitions.h"

gr::base::VAO::VAO()
{
	glGenVertexArrays(1, &ID);
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
