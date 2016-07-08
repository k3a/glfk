/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "Renderer.h"

#include <map>

/// Framebufer Object (FBO)
class BaseFramebuffer : public GLObject
{
public:
    enum Status {
        /// framebuffer is complete
        COMPLETE = GL_FRAMEBUFFER_COMPLETE,
        /// framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist
        UNDEFINED = GL_FRAMEBUFFER_UNDEFINED,
        /// any of the framebuffer attachment points are framebuffer incomplete
        INCOMPLETE_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
        /// framebuffer does not have at least one image attached to it
        INCOMPLETE_MISSING_ATTACHMENT = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
        /// the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi
        INCOMPLETE_DRAW_BUFFER = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
        /// GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER
        INCOMPLETE_READ_BUFFER = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
        /// combination of internal formats of the attached images violates an implementation-dependent set of restrictions
        UNSUPPORTED = GL_FRAMEBUFFER_UNSUPPORTED,
        /// value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the
        /// not same for all attached textures; or, if the attached images are a mix of renderbuffers and textures, the value of
        /// GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES
        INCOMPLETE_MULTISAMPLE = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
        /// value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached images
        /// are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures.
        FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
        /// any framebuffer attachment is layered, and any populated attachment is not layered, or if all
        /// populated color attachments are not from textures of the same target.
        INCOMPLETE_LAYER_TARGETS = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
    };
    
    enum CubeFace {
        POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    
    BaseFramebuffer();

    BaseFramebuffer& Bind(GLenum target);
    static void BindNone(GLenum target);
    BaseFramebuffer& Unbind(GLenum target){ BindNone(target); return *this; };
    
    Status CheckStatus(GLenum target);
    BaseFramebuffer& AttachRenderbuffer(GLenum target, GLenum attachment, GLuint renderbuffer);
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    BaseFramebuffer& AttachTexture1D(GLenum target, GLenum attachment, GLuint texture, GLint level);
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    BaseFramebuffer& AttachTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    /// \param level Mipmap level of the texture object to attach (0 = base).
    /// \param layer Layer of the 3D texture to attach as a 2D texture
    BaseFramebuffer& AttachTexture3D(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
    
    // helpers
    BaseFramebuffer& AttachTextureCube(GLenum target, GLenum attachment, CubeFace face, GLuint texture, GLint level) {
        return AttachTexture2D(target, attachment, face, texture, level);
    }
    BaseFramebuffer& AttachTexture2D(GLenum target, GLenum attachment, GLuint texture, GLint level) {
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
    
    Status CheckStatus() { return BaseFramebuffer::CheckStatus(_target); };
    FramebufferWithTarget& AttachRenderbuffer(GLenum attachment, GLuint renderbuffer) {
        return (FramebufferWithTarget&)BaseFramebuffer::AttachRenderbuffer(_target, attachment, renderbuffer);
    };
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    FramebufferWithTarget& AttachTexture1D(GLenum attachment, GLuint texture, GLint level){
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTexture1D(_target, attachment, texture, level);
    };
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    FramebufferWithTarget& AttachTexture2D(GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTexture2D(_target, attachment, textarget, texture, level);
    }
    /// \param level Mipmap level of the texture object to attach (0 = base).
    /// \param layer Layer of the 3D texture to attach as a 2D texture
    FramebufferWithTarget& AttachTexture3D(GLenum attachment, GLuint texture, GLint level, GLint layer){
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTexture3D(_target, attachment, texture, level, layer);
    }
    
    // helpers
    FramebufferWithTarget& Clear(GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT){
        return (FramebufferWithTarget&)BaseFramebuffer::Clear(_target, mask);
    };
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    FramebufferWithTarget& AttachTextureCube(GLenum attachment, CubeFace face, GLuint texture, GLint level) {
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTextureCube(_target, attachment, face, texture, level);
    }
    /// \param level Specifies the mipmap level of the texture object to attach (0 = base).
    FramebufferWithTarget& AttachTexture2D(GLenum attachment, GLuint texture, GLint level) {
        return (FramebufferWithTarget&)BaseFramebuffer::AttachTexture2D(_target, attachment, texture, level);
    }
    
private:
    GLenum _target;
};

/// Framebuffer Object (FBO) for target GL_FRAMEBUFFER
class Framebuffer : public FramebufferWithTarget
{
public:
    Framebuffer() : FramebufferWithTarget(GL_FRAMEBUFFER) {};
};

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
