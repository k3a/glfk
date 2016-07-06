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
    /// Links the attached shaders. Possible errors returned by GetInfoLog().
    bool Link();
    /// Validates the program can run in the current GL state. Possible errors returned by GetInfoLog().
    Program& Validate();
    std::string GetInfoLog()const;
    bool IsValid()const{return _valid;};
    Program& Use();
    Program& Bind(){ return Use(); };
    GLint GetInt(GLenum pname)const;
    
    Attribute GetAttribute(const std::string& name);
    Uniform GetUniform(const std::string& name);
    
    template <typename T>
    Program& SetUniform(const std::string& name, const T& value)
    {
        return SetUniform(GetUniform(name), value);
    }
    
    template <typename T>
    Program& SetUniformTextureUnit(const std::string& name, const T& value)
    {
        return SetUniformTextureUnit(GetUniform(name), value);
    }
    
    template <typename T>
    Program& SetUniformInt(const std::string& name, const T& x, const T& y)
    {
        return SetUniformInt(GetUniform(name), x, y);
    }
    template <typename T>
    Program& SetUniform(const std::string& name, const T& x, const T& y)
    {
        return SetUniform(GetUniform(name), x, y);
    }
    Program& SetUniform(const std::string& name, double x, double y)
    {
        return SetUniform(GetUniform(name), (float)x, (float)y);
    }
    
    template <typename T>
    Program& SetUniformInt(const std::string& name, const T& x, const T& y, const T& z)
    {
        return SetUniformInt(GetUniform(name), x, y, z);
    }
    template <typename T>
    Program& SetUniform(const std::string& name, const T& x, const T& y, const T& z)
    {
        return SetUniform(GetUniform(name), x, y, z);
    }
    Program& SetUniform(const std::string& name, double x, double y, double z)
    {
        return SetUniform(GetUniform(name), (float)x, (float)y, (float)z);
    }
    
    template <typename T>
    Program& SetUniformInt(const std::string& name, const T& x, const T& y, const T& z, const T& w)
    {
        return SetUniformInt(GetUniform(name), x, y, z, w);
    }
    template <typename T>
    Program& SetUniform(const std::string& name, const T& x, const T& y, const T& z, const T& w)
    {
        return SetUniform(GetUniform(name), x, y, z, w);
    }
    Program& SetUniform(const std::string& name, double x, double y, double z, double w)
    {
        return SetUniform(GetUniform(name), (float)x, (float)y, (float)z, (float)w);
    }
    
    template <typename T>
    Program& SetUniform( const std::string& name, const T* values, unsigned count)
    {
        return SetUniform(GetUniform(name), values, count);
    }
    
    Program& SetUniformInt(const Uniform& uniform, int value);
    Program& SetUniformTextureUnit(const Uniform& uniform, int unit){ return SetUniformInt(uniform, unit); };
    Program& SetUniformInt(const Uniform& uniform, int x, int y);
    Program& SetUniformInt(const Uniform& uniform, int x, int y, int z);
    Program& SetUniformInt(const Uniform& uniform, int x, int y, int z, int w);
    Program& SetUniform(const Uniform& uniform, float value);
    Program& SetUniform(const Uniform& uniform, float x, float y);
    Program& SetUniform(const Uniform& uniform, float x, float y, float z);
    Program& SetUniform(const Uniform& uniform, float x, float y, float z, float w);
    Program& SetUniform(const Uniform& uniform, const int* values, unsigned count);
    Program& SetUniform(const Uniform& uniform, const float* values, unsigned count);
    
#ifdef GLFK_HAS_GLM
    Program& SetUniform(const Uniform& uniform, const glm::vec2& value);
    Program& SetUniform(const Uniform& uniform, const glm::vec3& value);
    Program& SetUniform(const Uniform& uniform, const glm::vec4& value);
    Program& SetUniform(const Uniform& uniform, const glm::vec2* values, unsigned count);
    Program& SetUniform(const Uniform& uniform, const glm::vec3* values, unsigned count);
    Program& SetUniform(const Uniform& uniform, const glm::vec4* values, unsigned count);
    Program& SetUniform(const Uniform& uniform, const glm::mat3x3& value);
    Program& SetUniform(const Uniform& uniform, const glm::mat4x4& value);
#endif
    
    // helpers
    unsigned GetNumActiveAttributes()const{ return GetInt(GL_ACTIVE_ATTRIBUTES); };
    unsigned GetNumActiveUniforms()const{ return GetInt(GL_ACTIVE_UNIFORMS); };
    
private:
    GLuint _program;
    bool _valid;
};


