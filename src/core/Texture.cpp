/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "Texture.h"

#ifdef GLFK_PREVENT_MULTIPLE_BIND
unsigned TextureUnit::s_activeUnit = 0;
#endif

TextureUnit::TextureUnit(unsigned unit)
: _unit(unit)
{
    if (unit < GL_TEXTURE0)
        unit = GL_TEXTURE0 + unit;
    
    _unit = unit - GL_TEXTURE0;
}

TextureUnit& TextureUnit::Bind()
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_activeUnit == _unit)
        return *this;
    s_activeUnit = _unit;
#endif
    
    glActiveTexture(GL_TEXTURE0 + _unit);
    return *this;
}

void TextureUnit::BindNone()
{
    // set at last unit to allow independent unbinds and binds
    // without replacing active texture for lower units
    unsigned unitToSet = Renderer::GetMaxTextureUnits()-1;
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_activeUnit == unitToSet)
        return;
    s_activeUnit = unitToSet;
#endif
    
    glActiveTexture(GL_TEXTURE0 + unitToSet);
}

GLint TextureUnit::GetInt(GLenum target, GLenum pname)
{
    GLint out;
    glGetTexParameteriv(target, pname, &out);
    return out;
}

TextureUnit& TextureUnit::SetInt(GLenum target, GLenum pname, GLint value)
{
    glTexParameteri(target, pname, value);
    return *this;
}

TextureUnit& TextureUnit::SetWrap(GLenum target, WrapMode::E s)
{
    return SetInt(target, GL_TEXTURE_WRAP_S, s);
}
TextureUnit& TextureUnit::SetWrap(GLenum target, WrapMode::E s, WrapMode::E t)
{
    return SetInt(target, GL_TEXTURE_WRAP_S, s).SetInt(target, GL_TEXTURE_WRAP_T, t);
}
TextureUnit& TextureUnit::SetWrap(GLenum target, WrapMode::E s, WrapMode::E t, WrapMode::E r)
{
    return SetInt(target, GL_TEXTURE_WRAP_S, s).SetInt(target, GL_TEXTURE_WRAP_T, t).SetInt(target, GL_TEXTURE_WRAP_R, r);
}
TextureUnit& TextureUnit::SetFilter(GLenum target, MinFilterMode::E minifying, MagFilterMode::E magnifying)
{
    return SetInt(target, GL_TEXTURE_MIN_FILTER, minifying).SetInt(target, GL_TEXTURE_MAG_FILTER, magnifying);
}

//----------------------------------------------------------

#ifdef GLFK_PREVENT_MULTIPLE_BIND
BaseTexture::TargetTextureMap BaseTexture::s_boundTextureToTarget;
#endif

BaseTexture::BaseTexture()
: _valid(false)
{
    GLuint obj;
    glGenTextures(1, &obj);
    
    AssignGLObject(obj, glDeleteTextures);
}

BaseTexture& BaseTexture::Bind(GLenum target)
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundTextureToTarget[target] == *this)
        return *this;
    s_boundTextureToTarget[target] = *this;
#endif
    glBindTexture(target, *this);
    return *this;
}

void BaseTexture::BindNone(GLenum target)
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundTextureToTarget[target] == 0)
        return;
    s_boundTextureToTarget[target] = 0;
#endif
    glBindTexture(target, 0);
}

BaseTexture& BaseTexture::GenerateMipmap(GLenum target)
{
#ifdef DEBUG
    assert( IsValid() ); // texture must be valid (hold data)
#endif
    
    GLFK_AUTO_BIND(target);
    glGenerateMipmap(target);
    GLFK_AUTO_UNBIND(target);
    return *this;
}

//----------------------------------------------------------

Texture& Texture::SetTextureUnit(TextureUnit unit)
{
    _unit = unit;
    
    unit.Bind();
    
    glBindTexture(_target, *this); // force-bind
    
    // set at last unit to allow independent unbinds and binds
    // without replacing active texture for lower units
    unit.Unbind();
    
    GLFK_AUTO_UNBIND(); // because of force-bind earlier
    return *this;
}

//----------------------------------------------------------

Texture1D& Texture1D::SetImage(GLint level, InternalFormat::E internalFormat, GLsizei width, PixelDataFormat::E format, PixelDataType::E type, const GLvoid * data)
{
    GLFK_AUTO_BIND();
    glTexImage1D(_target, level, internalFormat, width, 0, format, type, data);
    _valid = true;
    GLFK_AUTO_UNBIND();
    return *this;
}

//----------------------------------------------------------

Texture2D& Texture2D::SetImage(GLint level, InternalFormat::E internalFormat, GLsizei width, GLsizei height,
                                PixelDataFormat::E format, PixelDataType::E type, const GLvoid * data)
{
    GLFK_AUTO_BIND();
    glTexImage2D(_target, level, internalFormat, width, height, 0, format, type, data);
    _valid = true;
    GLFK_AUTO_UNBIND();
    return *this;
}

//----------------------------------------------------------

Texture3D& Texture3D::SetImage(GLint level, InternalFormat::E internalFormat, GLsizei width, GLsizei height,
                    GLsizei depth, PixelDataFormat::E format, PixelDataType::E type, const GLvoid * data)
{
    GLFK_AUTO_BIND();
    glTexImage3D(_target, level, internalFormat, width, height, depth, 0, format, type, data);
    _valid = true;
    GLFK_AUTO_UNBIND();
    return *this;
}

//----------------------------------------------------------

TextureCube& TextureCube::SetImage(CubeFace::E face, GLint level, InternalFormat::E internalFormat, GLsizei width, GLsizei height,
                                        PixelDataFormat::E format, PixelDataType::E type, const GLvoid * data)
{
    GLFK_AUTO_BIND();
    glTexImage2D(face, level, internalFormat, width, height, 0, format, type, data);
    _valid = true;
    GLFK_AUTO_UNBIND();
    return *this;
}




