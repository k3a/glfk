#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &_array);
	PrintGLError("creating VAO");
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_array);
	PrintGLError("deleting VAO");
}

VertexArray& VertexArray::Bind()
{
	glBindVertexArray(_array);
	PrintGLError("binding VAO");
	return *this;
}
void VertexArray::BindNone()
{
	glBindVertexArray(0);
	PrintGLError("binding 0 VAO");
}

VertexArray& VertexArray::EnableAttribArray(GLuint index, bool enable)
{
	Bind();
	if (enable)
		glEnableVertexAttribArray(index);
	else 
		glDisableVertexAttribArray(index);

	PrintGLError("Enabling or disabling vertex attrib array for VAO");
	return *this;
}

