/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "Renderer.h"
#include "Utils.h"

/// Base Texture
class BaseTexture : public NoCopy
{
public:
    enum WrapMode {
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
        REPEAT = GL_REPEAT
    };
    
    BaseTexture();
    ~BaseTexture();
    
    BaseTexture& Bind(GLenum target);
    static void BindNone(GLenum target);
    BaseTexture& Unbind(GLenum target){ BindNone(target); return *this; };
    GLint GetInt(GLenum target, GLenum pname);
    BaseTexture& SetInt(GLenum target, GLenum pname, GLint value);
    
    /// Sets as active texture for a specified unit (starting from 0 which specifies GL_TEXTURE0).
    /// You can also specify GL constant here like GL_TEXTURE0
    BaseTexture& SetToUnit(GLenum target, unsigned unit);
    unsigned GetUnit(){ return _unit; };
    
    BaseTexture& GenerateMipmap(GLenum target);
    
    // helpers
    BaseTexture& SetWrap(GLenum target, WrapMode s);
    BaseTexture& SetWrap(GLenum target, WrapMode s, WrapMode t);
    BaseTexture& SetWrap(GLenum target, WrapMode s, WrapMode t, WrapMode r);
    
private:
    GLuint _texture;
    unsigned _unit;
};

/// Texture for a specific target
class Texture : public BaseTexture
{
public:
    Texture(GLenum target) : _target(target) {};
    
    Texture& Bind();
    Texture& Unbind();
    GLint GetInt(GLenum pname){ return BaseTexture::GetInt(_target, pname); };
    BaseTexture& SetInt(GLenum pname, GLint value){ return (Texture&)BaseTexture::SetInt(_target, pname, value); };
    
    /// Sets as active texture for a specified unit (starting from 0 which specifies GL_TEXTURE0).
    /// You can also specify GL constant here like GL_TEXTURE0
    BaseTexture& SetToUnit(unsigned unit){ return (Texture&)BaseTexture::SetToUnit(_target, unit); };
    
    Texture& GenerateMipmap(){ return (Texture&)BaseTexture::GenerateMipmap(_target); };
    
    // helpers
    BaseTexture& SetWrap(GLenum target, WrapMode s){ return (Texture&)BaseTexture::SetWrap(_target, s); };
    BaseTexture& SetWrap(GLenum target, WrapMode s, WrapMode t){ return (Texture&)BaseTexture::SetWrap(_target, s, t); };
    BaseTexture& SetWrap(GLenum target, WrapMode s, WrapMode t, WrapMode r){ return (Texture&)BaseTexture::SetWrap(_target, s, t, r); };
    
protected:
    GLenum _target;
};

/// Texture for GL_TEXTURE_1D
class Texture1D : public Texture
{
public:
    Texture1D() : Texture(GL_TEXTURE_1D) {};
    
    /// Sets the texture image data
    /// \param internalFormat How to represent the texture in GL
    /// \param format Format of supplied data
    /// \param type Data type of each channel
    Texture1D& SetImage(GLint level, GLint internalFormat, GLsizei width,
                        GLenum format, GLenum type, const GLvoid * data);
};

/// Texture for GL_TEXTURE_2D
class Texture2D : public Texture
{
public:
    Texture2D() : Texture(GL_TEXTURE_2D) {};
    
    /// Sets the texture image data
    /// \param internalFormat How to represent the texture in GL
    /// \param format Format of supplied data
    /// \param type Data type of each channel
    Texture2D& SetImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                        GLenum format, GLenum type, const GLvoid * data);
};

/// Texture for GL_TEXTURE_3D
class Texture3D : public Texture
{
public:
    Texture3D() : Texture(GL_TEXTURE_3D) {};
    
    /// Sets the texture image data
    /// \param internalFormat How to represent the texture in GL
    /// \param format Format of supplied data
    /// \param type Data type of each channel
    Texture3D& SetImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth,
                        GLenum format, GLenum type, const GLvoid * data);
};

/// Texture for GL_TEXTURE_CUBE_MAP
class TextureCubeMap : public Texture
{
public:
    enum CubeFace {
        POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    
    TextureCubeMap() : Texture(GL_TEXTURE_CUBE_MAP) {};
    
    /// Sets the texture image data
    /// \param internalFormat How to represent the texture in GL
    /// \param format Format of supplied data
    /// \param type Data type of each channel
    TextureCubeMap& SetImage(CubeFace face, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                            GLenum format, GLenum type, const GLvoid * data);
};




