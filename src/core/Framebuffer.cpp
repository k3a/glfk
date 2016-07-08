/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "Framebuffer.h"

#ifdef GLFK_PREVENT_MULTIPLE_BIND
BaseFramebuffer::TargetFramebufferMap BaseFramebuffer::s_boundFramebufferToTarget;
#endif

BaseFramebuffer::BaseFramebuffer()
{
    GLuint obj;
    glGenFramebuffers(1, &obj);
    PrintGLError("generating framebuffer");
    
    AssignGLObject(obj, glDeleteFramebuffers);
}

BaseFramebuffer& BaseFramebuffer::Bind(GLenum target)
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundFramebufferToTarget[target] == *this)
        return *this;
    s_boundFramebufferToTarget[target] = *this;
#endif
    glBindFramebuffer(target, *this);
    PrintGLError("binding framebuffer");
    return *this;
}
void BaseFramebuffer::BindNone(GLenum target)
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundFramebufferToTarget[target] == 0)
        return;
    s_boundFramebufferToTarget[target] = 0;
#endif
    glBindFramebuffer(target, 0);
    PrintGLError("binding 0 framebuffer");
}

BaseFramebuffer::Status BaseFramebuffer::CheckStatus(GLenum target)
{
    GLFK_AUTO_BIND(target);
    
    GLenum ret = glCheckFramebufferStatus(target);
    PrintGLError("checking framebuffer");
    
    GLFK_AUTO_UNBIND(target);
    return (Status)ret;
}

BaseFramebuffer& BaseFramebuffer::AttachRenderbuffer(GLenum target, GLenum attachment, GLuint renderbuffer)
{
    GLFK_AUTO_BIND(target);
    
    glFramebufferRenderbuffer(target, attachment, GL_RENDERBUFFER, renderbuffer);
    PrintGLError("attaching renderbuffer into framebuffer");
    
    GLFK_AUTO_UNBIND(target);
    return *this;
}

BaseFramebuffer& BaseFramebuffer::AttachTexture1D(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
    GLFK_AUTO_BIND(target);
    
    glFramebufferTexture1D(target, attachment, GL_TEXTURE_1D, texture, level);
    PrintGLError("binding 1d texture into framebuffer");
    
    GLFK_AUTO_UNBIND(target);
    return *this;
}

BaseFramebuffer& BaseFramebuffer::AttachTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    GLFK_AUTO_BIND(target);
    
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
    PrintGLError("binding 2d texture into framebuffer");
    /*GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);*/
    GLFK_AUTO_UNBIND(target);
    return *this;
}

BaseFramebuffer& BaseFramebuffer::AttachTexture3D(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
    GLFK_AUTO_BIND(target);
    
    glFramebufferTexture3D(target, attachment, GL_TEXTURE_3D, texture, level, layer);
    PrintGLError("binding 3d texture into framebuffer");
    
    GLFK_AUTO_UNBIND(target);
    return *this;
}

BaseFramebuffer& BaseFramebuffer::Clear(GLenum target, GLbitfield mask)
{
    GLFK_AUTO_BIND(target);
    
    Renderer::Clear();
    
    GLFK_AUTO_UNBIND(target);
    return *this;
}
