/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "Buffer.h"

BaseBuffer::BaseBuffer(VertexArray& vao)
{
    GLFK_AUTO_BIND_OBJ(vao);
    glGenBuffers(1, &_buffer);
    PrintGLError("generating buffer");
    GLFK_AUTO_UNBIND_OBJ(vao);
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

BaseBuffer& BaseBuffer::SetData(GLenum target, GLsizeiptr size, const GLvoid * data, Usage usage)
{
    GLFK_AUTO_BIND(target);
    glBufferData(target, size, data, usage);
    PrintGLError("setting buffer data");
    GLFK_AUTO_UNBIND(target);
    return *this;
}

//--------------------------------------------------

Buffer::Buffer(VertexArray& vao, GLenum target)
: BaseBuffer(vao), _target(target)
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

Buffer& Buffer::SetData(GLsizeiptr size, const GLvoid * data, Usage usage)
{
    BaseBuffer::SetData(_target, size, data, usage);
    return *this;
}

//-------------------------------------------------

ArrayBuffer& ArrayBuffer::SetAttribPointer(GLuint index, GLint size, AttribType type,
        bool normalized, GLsizei stride, const GLvoid * pointer)
{
    GLFK_AUTO_BIND();
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    PrintGLError("setting vertex attrib pointer");
    GLFK_AUTO_UNBIND();
    return *this;
}

