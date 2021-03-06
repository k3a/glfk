/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#include "Buffer.h"

#ifdef GLFK_PREVENT_MULTIPLE_BIND
BaseBuffer::TargetBufferMap BaseBuffer::s_boundBufferToTarget;
#endif

BaseBuffer::BaseBuffer(VertexArray vao)
: _vao(vao)
{
    GLFK_AUTO_BIND_OBJ(vao);
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    
    AssignGLObject(buffer, glDeleteBuffers);
    
    GLFK_AUTO_UNBIND_OBJ(vao);
}

BaseBuffer& BaseBuffer::Bind(GLenum target) 
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundBufferToTarget[target] == *this)
        return *this;
    s_boundBufferToTarget[target] = *this;
#endif
    glBindBuffer(target, *this);
    return *this;
}
void BaseBuffer::BindNone(GLenum target)
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundBufferToTarget[target] == 0)
        return;
    s_boundBufferToTarget[target] = 0;
#endif
    glBindBuffer(target, 0);
}

BaseBuffer& BaseBuffer::SetData(GLenum target, GLsizeiptr size, const GLvoid * data, BufferUsage::E usage)
{
    GLFK_AUTO_BIND(target);
    glBufferData(target, size, data, usage);
    GLFK_AUTO_UNBIND(target);
    return *this;
}

//-----------------------------------------------------------------------

ArrayBuffer& ArrayBuffer::SetAttribPointer(GLuint index, GLint size, AttribType::E type,
                                bool normalized, GLsizei stride, const GLvoid * pointer)
{
    GLFK_AUTO_BIND();
    _vao.EnableAttribArray(index);
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    GLFK_AUTO_UNBIND();
    return *this;
}


