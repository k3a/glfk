/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#pragma once

#include "Renderer.h"

/// Renderbuffer object
class Renderbuffer : public GLObject
{
public:
    
    Renderbuffer();
    Renderbuffer(InternalFormat::E internalformat, GLsizei width, GLsizei height);

    Renderbuffer& Bind();
    static void BindNone();
    Renderbuffer& Unbind(){ BindNone(); return *this; };
    
    /// Set storage for the renderbuffer
    Renderbuffer& SetStorage(InternalFormat::E internalformat, GLsizei width, GLsizei height);

private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    static GLuint s_boundRenderbuffer;
#endif
};
