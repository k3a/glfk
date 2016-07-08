/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include <map>
#include "Renderer.h"
#include "Utils.h"

/// Texture Unit
/// Device supports several texture units (actually Renderer::GetMaxTextureUnits) counted from 0.
/// TextureUnit for unber one specifies GL_TEXTURE0.
class TextureUnit
{
    friend class Texture;
private:
    TextureUnit() : _unit(0) {};
    
public:
    TextureUnit(unsigned unit);
    
    operator unsigned()const{ return _unit; };
    
    TextureUnit& Bind();
    static void BindNone();
    TextureUnit& Unbind(){ BindNone(); return *this; };
    
    GLint GetInt(GLenum target, GLenum pname);
    TextureUnit& SetInt(GLenum target, GLenum pname, GLint value);
    
    // helpers ---
    
    TextureUnit& SetWrap(GLenum target, WrapMode::E s);
    TextureUnit& SetWrap(GLenum target, WrapMode::E s, WrapMode::E t);
    TextureUnit& SetWrap(GLenum target, WrapMode::E s, WrapMode::E t, WrapMode::E r);
    
    /// Set texture filtering mode
    /// The initial value of minifying is E::MIN_NEAREST_MIPMAP_LINEAR, for magnifying E::MAG_LINEAR
    TextureUnit& SetFilter(GLenum target, MinFilterMode::E minifying, MagFilterMode::E magnifying);
    
private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    static unsigned s_activeUnit;
#endif
    unsigned _unit;
};

/// Base Texture
class BaseTexture : public GLObject
{
public:
    BaseTexture();
    
    BaseTexture& Bind(GLenum target);
    static void BindNone(GLenum target);
    BaseTexture& Unbind(GLenum target){ BindNone(target); return *this; };
    
    BaseTexture& GenerateMipmap(GLenum target);
    
    // helpers
    static unsigned GetMaxTextureSize(){ return Renderer::GetInt(GL_MAX_TEXTURE_SIZE); };
    
private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    typedef std::map<GLenum, GLuint> TargetTextureMap;
    static TargetTextureMap s_boundTextureToTarget;
#endif
};

/// Texture for a specific target
class Texture : public BaseTexture
{
public:
    Texture(GLenum target) : _target(target) {};
    
    Texture& Bind() { return (Texture&)BaseTexture::Bind(_target); };
    Texture& Unbind() { return (Texture&)BaseTexture::Unbind(_target); };
    void BindNone() { BaseTexture::BindNone(_target); }
    
    GLenum GetTarget()const{ return _target; };
    GLint GetInt(TextureUnit& unit, GLenum pname){ return unit.GetInt(_target, pname); };
    Texture& SetInt(TextureUnit& unit, GLenum pname, GLint value){ unit.SetInt(_target, pname, value); return *this; };
    Texture& SetTextureUnit(TextureUnit unit);
    TextureUnit& GetTextureUnit(){ return _unit; };
    
    Texture& GenerateMipmap(){ return (Texture&)BaseTexture::GenerateMipmap(_target); };
    
    // helpers ---
    
    Texture& SetWrap(WrapMode::E s){ _unit.SetWrap(_target, s); return *this; };
    Texture& SetWrap(WrapMode::E s, WrapMode::E t){ _unit.SetWrap(_target, s, t); return *this; };
    Texture& SetWrap(WrapMode::E s, WrapMode::E t, WrapMode::E r){ _unit.SetWrap(_target, s, t, r); return *this; };
    
    /// Set texture filtering mode
    /// The initial value of minifying is E::MIN_NEAREST_MIPMAP_LINEAR, for magnifying E::MAG_LINEAR
    Texture& SetFilter(MinFilterMode::E minifying, MagFilterMode::E magnifying){ _unit.SetFilter(_target, minifying, magnifying); return *this; };
    
protected:
    GLenum _target;
    TextureUnit _unit;
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
    
    // helpers
    Texture1D& SetEmptyImage(GLint internalFormat, GLsizei width, GLenum format/* = GL_RGBA*/) {
        return SetImage(0, internalFormat, width, format, GL_UNSIGNED_BYTE, NULL);
    }
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

    // helpers
    Texture2D& SetEmptyImage(GLint internalFormat, GLsizei width, GLsizei height) {
        return SetImage(0, internalFormat, width, height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
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
    
    // helpers
    Texture3D& SetEmptyImage(GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth) {
        return SetImage(0, internalFormat, width, height, depth, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
};

/// Texture for GL_TEXTURE_CUBE_MAP
class TextureCube : public Texture
{
public:
    
    TextureCube() : Texture(GL_TEXTURE_CUBE_MAP) {};
    
    /// Sets the texture image data
    /// \param internalFormat How to represent the texture in GL
    /// \param format Format of supplied data
    /// \param type Data type of each channel
    TextureCube& SetImage(CubeFace::E face, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                            GLenum format, GLenum type, const GLvoid * data);
    
    // helpers
    TextureCube& SetEmptyImage(CubeFace::E face, GLint internalFormat, GLsizei width, GLsizei height) {
        return SetImage(face, 0, internalFormat, width, height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    }
};




