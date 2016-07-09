/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "Renderbuffer.h"

#ifdef GLFK_PREVENT_MULTIPLE_BIND
GLuint Renderbuffer::s_boundRenderbuffer;
#endif

Renderbuffer::Renderbuffer()
{
    GLuint obj;
    glGenRenderbuffers(1, &obj);
    
    AssignGLObject(obj, glDeleteRenderbuffers);
}

Renderbuffer::Renderbuffer(InternalFormat::E internalformat, GLsizei width, GLsizei height)
{
    GLuint obj;
    glGenRenderbuffers(1, &obj);
    
    AssignGLObject(obj, glDeleteRenderbuffers);
    
    SetStorage(internalformat, width, height);
}

Renderbuffer& Renderbuffer::Bind()
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundRenderbuffer == *this)
        return *this;
    s_boundRenderbuffer = *this;
#endif
    glBindRenderbuffer(GL_RENDERBUFFER, *this);
    return *this;
}

void Renderbuffer::BindNone()
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundRenderbuffer == 0)
        return;
    s_boundRenderbuffer = 0;
#endif
    glBindBuffer(GL_RENDERBUFFER, 0);
}

Renderbuffer& Renderbuffer::SetStorage(InternalFormat::E internalformat, GLsizei width, GLsizei height)
{
    GLFK_AUTO_BIND();
    
    glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
    
    GLFK_AUTO_UNBIND();
    return *this;
}
