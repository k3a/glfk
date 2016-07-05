#include "Buffer.h"

BaseBuffer::BaseBuffer()
{
	glGenBuffers(1, &_buffer);
	PrintGLError("gener'g buffer");
}

BaseBuffer::~BaseBuffer()
{
	glDeleteBuffers(1, &_buffer);
	PrintGLError("deleting buffer");
}

BaseBuffer& BaseBuffer::Bind(GLenum target) 
{
	glBindBuffer(target, _buffer);
	PrintGLError("binding buffer");
	return *this;
}
void BaseBuffer::BindNone(GLenum target)
{
	glBindBuffer(target, 0);
	PrintGLError("binding 0 buffer");
}

BaseBuffer& BaseBuffer::SetData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage)
{
	Bind(target);
	glBufferData(target, size, data, usage);
	PrintGLError("setting buffer data");
#ifdef GLFK_UNBIND
	BindNone(target);
#endif
	return *this;
}

//--------------------------------------------------

Buffer::Buffer(GLenum target)
: _target(target)
{
}

Buffer& Buffer::Bind()
{
	BaseBuffer::Bind(_target);
	return *this;
}

Buffer& Buffer::Unbind()
{
	BaseBuffer::Unbind(_target);
	return *this;
}

Buffer& Buffer::SetData(GLsizeiptr size, const GLvoid * data, GLenum usage)
{
	BaseBuffer::SetData(_target, size, data, usage);
	return *this;
}

//-------------------------------------------------

ArrayBuffer& ArrayBuffer::SetAttribPointer(GLuint index, GLint size, GLenum type,
        GLboolean normalized, GLsizei stride, const GLvoid * pointer)
{
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	PrintGLError("setting vertex attrib pointer");
	return *this;
}

