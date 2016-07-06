/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "Renderer.h"
#include "Utils.h"
#include <string>

/// Class encapsulating Shader Object
class BaseShader : public NoCopy
{
    friend class Program;

public:
    BaseShader(GLenum shaderType);
    ~BaseShader();

    bool Compile();
    std::string GetInfoLog()const;
    BaseShader& SetSource(std::string str);
    bool IsValid()const{ return _valid; };

private:
    GLuint _shader;
    bool _valid;
};

/// Program object of type GL_VERTEX_SHADER
class VertexShader : public BaseShader
{
public:
    static BaseShader* FromString(std::string src) {
        return &(new BaseShader(GL_VERTEX_SHADER))->SetSource(src);
    };
    static BaseShader* FromFile(const char* path){ 
        return FromString(ReadFile(path));
    };
};

/// Program object of type GL_FRAGMENT_SHADER
class FragmentShader : public BaseShader
{
public:
    static BaseShader* FromString(std::string src) {
        return &(new BaseShader(GL_FRAGMENT_SHADER))->SetSource(src);
    };
    static BaseShader* FromFile(const char* path){ 
        return FromString(ReadFile(path));
    };
};

/// Program Object
class Program : public NoCopy
{
public:
    Program();
    ~Program();

    Program& AttachShader(const BaseShader& sh);
    bool Link();
    std::string GetInfoLog()const;
    bool IsValid()const{return _valid;};
    Program& Use();
    GLint GetInt(GLenum pname)const;

    // utils
    unsigned GetNumActiveAttributes()const{ return GetInt(GL_ACTIVE_ATTRIBUTES); };
    unsigned GetNumActiveUniforms()const{ return GetInt(GL_ACTIVE_UNIFORMS); };

private:
    GLuint _program;
    bool _valid;
};
