/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "Buffer.h"

#ifdef GLFK_PREVENT_MULTIPLE_BIND
BaseBuffer::TargetBufferMap BaseBuffer::s_boundBufferToTarget;
#endif

BaseBuffer::BaseBuffer(VertexArray& vao)
{
    GLFK_AUTO_BIND_OBJ(vao);
    
    GLuint buffer;
    glGenBuffers(1, &buffer);
    PrintGLError("generating buffer");
    
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
    PrintGLError("binding buffer");
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

