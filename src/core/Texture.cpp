/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "Texture.h"

BaseTexture::BaseTexture()
{
    glGenTextures(1, &_texture);
    PrintGLError("generating a texture");
}

BaseTexture::~BaseTexture()
{
    glDeleteTextures(1, &_texture);
    PrintGLError("deleting a texture");
}

BaseTexture& BaseTexture::Bind(GLenum target)
{
    glBindTexture(target, _texture);
    PrintGLError("binding a texture");
    return *this;
}

void BaseTexture::BindNone(GLenum target)
{
    glBindTexture(target, 0);
    PrintGLError("binding a texture");
}

BaseTexture& BaseTexture::SetToUnit(GLenum target, unsigned int unit)
{
    if (unit < GL_TEXTURE0)
        unit = GL_TEXTURE0 + unit;
    
    _unit = unit - GL_TEXTURE0;
    glActiveTexture(unit);
    PrintGLError("setting an active texture");
    Bind(target);
    glActiveTexture(GL_TEXTURE31); // set at last unit to allow unbinds
    PrintGLError("setting the last active texture");
    return *this;
}

BaseTexture& BaseTexture::GenerateMipmap(GLenum target)
{
    GLFK_AUTO_BIND(target);
    glGenerateMipmap(target);
    PrintGLError("generating a mipmap");
    GLFK_AUTO_UNBIND(target);
    return *this;
}

GLint BaseTexture::GetInt(GLenum target, GLenum pname)
{
    GLint out;
    glGetTexParameteriv(target, pname, &out);
    PrintGLError("getting int v texture param");
    return out;
}

BaseTexture& BaseTexture::SetInt(GLenum target, GLenum pname, GLint value)
{
    glTexParameteri(target, pname, value);
    PrintGLError("setting int texture param");
    return *this;
}

BaseTexture& BaseTexture::SetWrap(GLenum target, WrapMode s)
{
    return SetInt(target, GL_TEXTURE_WRAP_S, s);
}
BaseTexture& BaseTexture::SetWrap(GLenum target, WrapMode s, WrapMode t)
{
    return SetInt(target, GL_TEXTURE_WRAP_S, s);
    return SetInt(target, GL_TEXTURE_WRAP_T, t);
}
BaseTexture& BaseTexture::SetWrap(GLenum target, WrapMode s, WrapMode t, WrapMode r)
{
    return SetInt(target, GL_TEXTURE_WRAP_S, s);
    return SetInt(target, GL_TEXTURE_WRAP_T, t);
    return SetInt(target, GL_TEXTURE_WRAP_R, r);
}

//-----------------------------------------------
Texture& Texture::Bind()
{
    return (Texture&)BaseTexture::Bind(_target);
}
Texture& Texture::Unbind()
{
    BaseTexture::BindNone(_target);
    return *this;
}

//-----------------------------------------------

Texture1D& Texture1D::SetImage(GLint level, GLint internalFormat, GLsizei width, GLenum format, GLenum type, const GLvoid * data)
{
    GLFK_AUTO_BIND();
    glTexImage1D(_target, level, internalFormat, width, 0, format, type, data);
    PrintGLError("setting 1d texture image");
    GLFK_AUTO_UNBIND();
    return *this;
}

//-----------------------------------------------

Texture2D& Texture2D::SetImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                                GLenum format, GLenum type, const GLvoid * data)
{
    GLFK_AUTO_BIND();
    glTexImage2D(_target, level, internalFormat, width, height, 0, format, type, data);
    PrintGLError("setting 2d texture image");
    GLFK_AUTO_UNBIND();
    return *this;
}

//-----------------------------------------------

Texture3D& Texture3D::SetImage(GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                    GLsizei depth, GLenum format, GLenum type, const GLvoid * data)
{
    GLFK_AUTO_BIND();
    glTexImage3D(_target, level, internalFormat, width, height, depth, 0, format, type, data);
    PrintGLError("setting 3d texture image");
    GLFK_AUTO_UNBIND();
    return *this;
}

//-----------------------------------------------

TextureCubeMap& TextureCubeMap::SetImage(CubeFace face, GLint level, GLint internalFormat, GLsizei width, GLsizei height,
                                        GLenum format, GLenum type, const GLvoid * data)
{
    GLFK_AUTO_BIND();
    glTexImage2D(face, level, internalFormat, width, height, 0, format, type, data);
    PrintGLError("setting 2d image for cubemap");
    GLFK_AUTO_UNBIND();
    return *this;
}




