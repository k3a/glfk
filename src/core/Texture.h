/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#pragma once

#include <map>
#include "Renderer.h"
#include "Utils.h"

/// Texture Unit
/// Device supports several texture units (actually Renderer::GetMaxTextureUnits) counted from 0.
class TextureUnit
{
    friend class Texture;
private:
    TextureUnit() : _unit(0) {};
    
public:
    /** Create an object representing texture unit
     
    \param unit Unit to represent. Number 0 represents GL_TEXTURE0 but you can also specify the GL constant directly.
    */
    TextureUnit(unsigned unit);
    
    /// Returns texture unit numbered from 0
    operator unsigned()const{ return _unit; };
    
    /// Returns GL unit contant (GL_TEXTUREX)
    GLenum GetGLUnit()const{ return GL_TEXTURE0 + _unit; }
    
    /// Set the unit active
    TextureUnit& Bind();
    /// Set the last possible texture unit
    static void BindNone();
    /// Set the last possible texture unit
    TextureUnit& Unbind(){ BindNone(); return *this; };
    
    GLint GetInt(GLenum target, GLenum pname);
    TextureUnit& SetInt(GLenum target, GLenum pname, GLint value);
    
    // helpers ---
    
    /** Set wrapping mode
     
    Initially are all wrap modes set to WrapMode::REPEAT.
    */
    TextureUnit& SetWrap(GLenum target, WrapMode::E s);
    TextureUnit& SetWrap(GLenum target, WrapMode::E s, WrapMode::E t);
    TextureUnit& SetWrap(GLenum target, WrapMode::E s, WrapMode::E t, WrapMode::E r);
    
    /** Set texture filtering mode
     
    The initial value of minifying is E::MIN_NEAREST_MIPMAP_LINEAR, for magnifying E::MAG_LINEAR
    */
    TextureUnit& SetFilter(GLenum target, MinFilterMode::E minifying, MagFilterMode::E magnifying);
    
protected:
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
    
    bool IsValid()const{ return _valid; };
    BaseTexture& GenerateMipmap(GLenum target);
    
    // helpers
    /// Returns the maximum texture size
    static unsigned GetMaxTextureSize(){ return Renderer::GetInt(GL_MAX_TEXTURE_SIZE); };
    /// Sets the texture pixel data row alignment. GLFK default 1 (OpenGL default 4).
    static void SetUnpackAlignment(unsigned align){ glPixelStorei(GL_UNPACK_ALIGNMENT, align); };
    
private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    typedef std::map<GLenum, GLuint> TargetTextureMap;
    static TargetTextureMap s_boundTextureToTarget;
#endif
    
protected:
    bool _valid;
};

/// Texture for a specific target
class Texture : public BaseTexture
{
public:
    Texture(GLenum target) : _target(target) {};
    Texture(GLenum target, TextureUnit unit) : _target(target) { SetTextureUnit(unit); };
    
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
    
    /** Set wrapping mode
     
    \note Because this parameter is specified for the texture unit, make sure to first set SetTextureUnit() before calling this function
    if you are not using default "0" unit. You can also set the parameter via TextureUnit.
     
    Initially are all wrap modes set to WrapMode::REPEAT.
    */
    Texture& SetWrap(WrapMode::E s){ _unit.SetWrap(_target, s); return *this; };
    Texture& SetWrap(WrapMode::E s, WrapMode::E t){ _unit.SetWrap(_target, s, t); return *this; };
    Texture& SetWrap(WrapMode::E s, WrapMode::E t, WrapMode::E r){ _unit.SetWrap(_target, s, t, r); return *this; };
    
    /** Set texture filtering mode
    
    \note Because this parameter is specified for the texture unit, make sure to first set SetTextureUnit() before calling this function
    if you are not using default "0" unit. You can also set the parameter via TextureUnit.
     
    The initial value of minifying is E::MIN_NEAREST_MIPMAP_LINEAR, for magnifying E::MAG_LINEAR
    */
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
    Texture1D(TextureUnit unit) : Texture(GL_TEXTURE_1D, unit) {};
    
    /// Sets the texture image data
    /// \param internalFormat How to represent the texture in GL
    /// \param format Format of supplied data
    /// \param type Data type of each channel
    Texture1D& SetImage(GLint level, InternalFormat::E internalFormat, GLsizei width,
                        PixelDataFormat::E format, PixelDataType::E type, const GLvoid * data);
    
    // helpers
    Texture1D& SetEmptyImage(InternalFormat::E internalFormat, GLsizei width, PixelDataFormat::E format/* = PixelDataFormat::RGBA*/) {
        return SetImage(0, internalFormat, width, format, PixelDataType::UNSIGNED_BYTE, NULL);
    }
};

/// Texture for GL_TEXTURE_2D
class Texture2D : public Texture
{
public:
    Texture2D() : Texture(GL_TEXTURE_2D) {};
    Texture2D(TextureUnit unit) : Texture(GL_TEXTURE_2D, unit) {};
    
    /// Sets the texture image data
    /// \param internalFormat How to represent the texture in GL
    /// \param format Format of supplied data
    /// \param type Data type of each channel
    Texture2D& SetImage(GLint level, InternalFormat::E internalFormat, GLsizei width, GLsizei height,
                        PixelDataFormat::E format, PixelDataType::E type, const GLvoid * data);

    // helpers
    Texture2D& SetEmptyImage(InternalFormat::E internalFormat, GLsizei width, GLsizei height) {
        return SetImage(0, internalFormat, width, height, PixelDataFormat::RGBA, PixelDataType::UNSIGNED_BYTE, NULL);
    }
};

/// Texture for GL_TEXTURE_3D
class Texture3D : public Texture
{
public:
    Texture3D() : Texture(GL_TEXTURE_3D) {};
    Texture3D(TextureUnit unit) : Texture(GL_TEXTURE_3D, unit) {};
    
    /// Sets the texture image data
    /// \param internalFormat How to represent the texture in GL
    /// \param format Format of supplied data
    /// \param type Data type of each channel
    Texture3D& SetImage(GLint level, InternalFormat::E internalFormat, GLsizei width, GLsizei height, GLsizei depth,
                        PixelDataFormat::E format, PixelDataType::E type, const GLvoid * data);
    
    // helpers
    Texture3D& SetEmptyImage(InternalFormat::E internalFormat, GLsizei width, GLsizei height, GLsizei depth) {
        return SetImage(0, internalFormat, width, height, depth, PixelDataFormat::RGBA, PixelDataType::UNSIGNED_BYTE, NULL);
    }
};

/// Texture for GL_TEXTURE_CUBE_MAP
class TextureCube : public Texture
{
public:
    TextureCube() : Texture(GL_TEXTURE_CUBE_MAP) {};
    TextureCube(TextureUnit unit) : Texture(GL_TEXTURE_CUBE_MAP, unit) {};
    
    /// Sets the texture image data
    /// \param internalFormat How to represent the texture in GL
    /// \param format Format of supplied data
    /// \param type Data type of each channel
    TextureCube& SetImage(CubeFace::E face, GLint level, InternalFormat::E internalFormat, GLsizei width, GLsizei height,
                            PixelDataFormat::E format, PixelDataType::E type, const GLvoid * data);
    
    // helpers
    TextureCube& SetEmptyImage(CubeFace::E face, InternalFormat::E internalFormat, GLsizei width, GLsizei height) {
        return SetImage(face, 0, internalFormat, width, height, PixelDataFormat::RGBA, PixelDataType::UNSIGNED_BYTE, NULL);
    }
};




