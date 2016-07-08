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
    PrintGLError("generating renderbuffer");
    
    AssignGLObject(obj, glDeleteRenderbuffers);
}

Renderbuffer& Renderbuffer::Bind()
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundRenderbuffer == *this)
        return *this;
    s_boundRenderbuffer = *this;
#endif
    glBindRenderbuffer(GL_RENDERBUFFER, *this);
    PrintGLError("binding renderbuffer");
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
    PrintGLError("binding 0 renderbuffer");
}

Renderbuffer& Renderbuffer::SetStorage(GLenum internalformat, GLsizei width, GLsizei height)
{
    GLFK_AUTO_BIND();
    
    glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
    PrintGLError("setting storage of renderbuffer");
    
    GLFK_AUTO_UNBIND();
    return *this;
}