/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "Renderer.h"

/// Renderbuffer object
class Renderbuffer : public GLObject
{
public:
    
    Renderbuffer();

    Renderbuffer& Bind();
    static void BindNone();
    Renderbuffer& Unbind(){ BindNone(); return *this; };
    
    Renderbuffer& SetStorage(InternalFormat::E internalformat, GLsizei width, GLsizei height);

private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    static GLuint s_boundRenderbuffer;
#endif
};
