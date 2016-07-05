#pragma once

#include "Renderer.h"
#include "Utils.h"

class BaseBuffer : public NoCopy
{
public:
	BaseBuffer();
	~BaseBuffer();

	BaseBuffer& Bind(GLenum target);
	static void BindNone(GLenum target);
	BaseBuffer& Unbind(GLenum target){ BindNone(target); return *this; };
	BaseBuffer& SetData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage = GL_STATIC_DRAW);

private:
	GLuint _buffer;
};

class Buffer : public BaseBuffer
{
public:
	Buffer(GLenum target);
	Buffer& Bind();
	Buffer& Unbind();
	Buffer& SetData(GLsizeiptr size, const GLvoid * data, GLenum usage = GL_STATIC_DRAW);

private:
	GLenum _target;	
};

class ArrayBuffer : public Buffer
{
public:
	ArrayBuffer() : Buffer(GL_ARRAY_BUFFER) {};

	ArrayBuffer& SetAttribPointer(GLuint index, GLint size, GLenum type, 
			GLboolean normalized = GL_FALSE, GLsizei stride = 0, const GLvoid * pointer = NULL);
};
typedef ArrayBuffer VertexBuffer;

class ElementArrayBuffer : public Buffer
{
public:
    ElementArrayBuffer() : Buffer(GL_ELEMENT_ARRAY_BUFFER) {};
};
typedef ElementArrayBuffer IndexBuffer;


