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

typedef GLint Attribute;
typedef GLint Uniform;

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
    
    Attribute GetAttribute(const std::string& name);
    Uniform GetUniform(const std::string& name);
    
    template <typename T>
    void SetUniform(const std::string& name, const T& value)
    {
        SetUniform(GetUniform(name), value);
    }
    
    template <typename T>
    void SetUniform(const std::string& name, const T& x, const T& y)
    {
        SetUniform(GetUniform(name), x, y);
    }
    
    template <typename T>
    void SetUniform(const std::string& name, const T& x, const T& y, const T& z)
    {
        SetUniform(GetUniform(name), x, y, z);
    }
    
    template <typename T>
    void SetUniform(const std::string& name, const T& x, const T& y, const T& z, const T& w)
    {
        SetUniform(GetUniform(name), x, y, z, w);
    }
    
    template <typename T>
    void SetUniform( const std::string& name, const T* values, unsigned count)
    {
        SetUniform(GetUniform(name), values, count);
    }
    
    void SetUniformInt(const Uniform& uniform, int value);
    void SetUniformInt(const Uniform& uniform, int x, int y);
    void SetUniformInt(const Uniform& uniform, int x, int y, int z);
    void SetUniformInt(const Uniform& uniform, int x, int y, int z, int w);
    void SetUniform(const Uniform& uniform, float value);
    void SetUniform(const Uniform& uniform, float x, float y);
    void SetUniform(const Uniform& uniform, float x, float y, float z);
    void SetUniform(const Uniform& uniform, float x, float y, float z, float w);
    void SetUniform(const Uniform& uniform, const int* values, unsigned count);
    void SetUniform(const Uniform& uniform, const float* values, unsigned count);
#ifdef GLFK_HAS_GLM
    void SetUniform(const Uniform& uniform, const glm::vec2& value);
    void SetUniform(const Uniform& uniform, const glm::vec3& value);
    void SetUniform(const Uniform& uniform, const glm::vec4& value);
    void SetUniform(const Uniform& uniform, const glm::vec2* values, unsigned count);
    void SetUniform(const Uniform& uniform, const glm::vec3* values, unsigned count);
    void SetUniform(const Uniform& uniform, const glm::vec4* values, unsigned count);
    void SetUniform(const Uniform& uniform, const glm::mat3x3& value);
    void SetUniform(const Uniform& uniform, const glm::mat4x4& value);
#endif
    
    // utils
    unsigned GetNumActiveAttributes()const{ return GetInt(GL_ACTIVE_ATTRIBUTES); };
    unsigned GetNumActiveUniforms()const{ return GetInt(GL_ACTIVE_UNIFORMS); };

private:
    GLuint _program;
    bool _valid;
};


