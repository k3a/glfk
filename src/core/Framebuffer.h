/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#pragma once

#include "Renderer.h"

#include <map>

/// Framebufer Object (FBO)
class BaseFramebuffer : public GLObject
{
public:
    BaseFramebuffer();

    BaseFramebuffer& Bind(GLenum target);
    static void BindNone(GLenum target);
    BaseFramebuffer& Unbind(GLenum target){ BindNone(target); return *this; };
    
    FramebufferStatus::E CheckStatus(GLenum target);
    BaseFramebuffer& AttachRenderbuffer(GLenum target, FramebufferAttachment::E attachment, GLuint renderbuffer);
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    BaseFramebuffer& AttachTexture1D(GLenum target, FramebufferAttachment::E attachment, GLuint texture, GLint level);
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    BaseFramebuffer& AttachTexture2D(GLenum target, FramebufferAttachment::E attachment, GLenum textarget, GLuint texture, GLint level);
    /// \param level Mipmap level of the texture object to attach (0 = base).
    /// \param layer Layer of the 3D texture to attach as a 2D texture
    BaseFramebuffer& AttachTexture3D(GLenum target, FramebufferAttachment::E attachment, GLuint texture, GLint level, GLint layer);
    
    // helpers
    BaseFramebuffer& AttachTextureCube(GLenum target, FramebufferAttachment::E attachment, CubeFace::E face, GLuint texture, GLint level) {
        return AttachTexture2D(target, attachment, face, texture, level);
    }
    BaseFramebuffer& AttachTexture2D(GLenum target, FramebufferAttachment::E attachment, GLuint texture, GLint level) {
        return AttachTexture2D(target, attachment, GL_TEXTURE_2D, texture, level);
    }
    BaseFramebuffer& Clear(GLenum target, GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    unsigned GetMaxColorAttachments(){ return Renderer::GetInt(GL_MAX_COLOR_ATTACHMENTS); };

private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    typedef std::map<GLenum, GLuint> TargetFramebufferMap;
    static TargetFramebufferMap s_boundFramebufferToTarget;
#endif
};

/// Framebufer Object (FBO) with a specific target
class FramebufferWithTarget : public BaseFramebuffer
{
public:
    FramebufferWithTarget(GLenum target) : _target(target) {};
    
    FramebufferWithTarget& Bind(){ return (FramebufferWithTarget&)BaseFramebuffer::Bind(_target); };
    FramebufferWithTarget& Unbind(){ return (FramebufferWithTarget&)BaseFramebuffer::Unbind(_target); };
    
    GLenum GetTarget()const{ return _target; };
    
    FramebufferStatus::E CheckStatus() { return BaseFramebuffer::CheckStatus(_target); };
    FramebufferWithTarget& AttachRenderbuffer(FramebufferAttachment::E attachment, GLuint renderbuffer) {
        return (FramebufferWithTarget&)BaseFramebuffer::AttachRenderbuffer(_target, attachment, renderbuffer);
    };
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    FramebufferWithTarget& AttachTexture1D(FramebufferAttachment::E attachment, GLuint texture, GLint level){
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTexture1D(_target, attachment, texture, level);
    };
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    FramebufferWithTarget& AttachTexture2D(FramebufferAttachment::E attachment, GLenum textarget, GLuint texture, GLint level) {
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTexture2D(_target, attachment, textarget, texture, level);
    }
    /// \param level Mipmap level of the texture object to attach (0 = base).
    /// \param layer Layer of the 3D texture to attach as a 2D texture
    FramebufferWithTarget& AttachTexture3D(FramebufferAttachment::E attachment, GLuint texture, GLint level, GLint layer){
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTexture3D(_target, attachment, texture, level, layer);
    }
    
    /// Read data from framebuffer
    FramebufferWithTarget& ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, PixelCopyDataFormat::E format,
                                        PixelDataType::E type, GLvoid * data);
    
    // helpers
    FramebufferWithTarget& Clear(GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT){
        return (FramebufferWithTarget&)BaseFramebuffer::Clear(_target, mask);
    };
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    FramebufferWithTarget& AttachTextureCube(FramebufferAttachment::E attachment, CubeFace::E face, GLuint texture, GLint level) {
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTextureCube(_target, attachment, face, texture, level);
    }
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    FramebufferWithTarget& AttachTexture2D(FramebufferAttachment::E attachment, GLuint texture, GLint level) {
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTexture2D(_target, attachment, texture, level);
    }
    
protected:
    GLenum _target;
};

/// Framebuffer Object (FBO) for target GL_FRAMEBUFFER
class Framebuffer : public FramebufferWithTarget
{
public:
    Framebuffer() : FramebufferWithTarget(GL_FRAMEBUFFER) {};
    static Framebuffer& Screen();
};
Framebuffer& Screen();

/// Framebuffer Object (FBO) for target GL_DRAW_FRAMEBUFFER
class DrawFramebuffer : public FramebufferWithTarget
{
public:
    DrawFramebuffer() : FramebufferWithTarget(GL_DRAW_FRAMEBUFFER) {};
};

/// Framebuffer Object (FBO) for target GL_READ_FRAMEBUFFER
class ReadFramebuffer : public FramebufferWithTarget
{
public:
    ReadFramebuffer() : FramebufferWithTarget(GL_READ_FRAMEBUFFER) {};
};


