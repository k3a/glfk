/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#pragma once

#include "Renderer.h"
#include "Utils.h"
#include <string>

/// Class encapsulating Shader Object
class BaseShader : public GLObject
{
    friend class Program;

public:
    BaseShader(GLenum shaderType);
    void DeleteGLObject(GLuint obj);

    bool Compile();
    std::string GetInfoLog()const;
    BaseShader& SetSource(std::string str);
    bool IsValid()const{ return _valid; };

private:
    bool _valid;
};

/// Program object of type GL_VERTEX_SHADER
class VertexShader : public BaseShader
{
public:
    VertexShader() : BaseShader(GL_VERTEX_SHADER) {};
    
    static VertexShader FromString(std::string src) {
        return (VertexShader&)VertexShader().SetSource(src);
    }
    
    static VertexShader FromFile(const char* path){
        return FromString(ReadFile(path));
    }
};

/// Program object of type GL_FRAGMENT_SHADER
class FragmentShader : public BaseShader
{
public:
    FragmentShader() : BaseShader(GL_FRAGMENT_SHADER) {};
    
    static FragmentShader FromString(std::string src) {
        return (FragmentShader&)FragmentShader().SetSource(src);
    }
    
    static FragmentShader FromFile(const char* path){
        return FromString(ReadFile(path));
    }
};

/// Program object of type GL_COMPUTE_SHADER
class ComputeShader : public BaseShader
{
public:
    ComputeShader() : BaseShader(GL_COMPUTE_SHADER) {};
    
    static ComputeShader FromString(std::string src) {
        return (ComputeShader&)ComputeShader().SetSource(src);
    }
    
    static ComputeShader FromFile(const char* path){
        return FromString(ReadFile(path));
    }
};

/// Program object of type GL_GEOMETRY_SHADER
class GeometryShader : public BaseShader
{
public:
    GeometryShader() : BaseShader(GL_GEOMETRY_SHADER) {};
    
    static GeometryShader FromString(std::string src) {
        return (GeometryShader&)GeometryShader().SetSource(src);
    }
    
    static GeometryShader FromFile(const char* path){
        return FromString(ReadFile(path));
    }
};

/// Program object of type GL_TESS_EVALUATION_SHADER
class TessEvaluationShader : public BaseShader
{
public:
    TessEvaluationShader() : BaseShader(GL_TESS_EVALUATION_SHADER) {};
    
    static TessEvaluationShader FromString(std::string src) {
        return (TessEvaluationShader&)TessEvaluationShader().SetSource(src);
    }
    
    static TessEvaluationShader FromFile(const char* path){
        return FromString(ReadFile(path));
    }
};

/// Program object of type GL_TESS_CONTROL_SHADER
class TessControlShader : public BaseShader
{
public:
    TessControlShader() : BaseShader(GL_TESS_CONTROL_SHADER) {};
    
    static TessControlShader FromString(std::string src) {
        return (TessControlShader&)TessControlShader().SetSource(src);
    }
    
    static TessControlShader FromFile(const char* path){
        return FromString(ReadFile(path));
    }
};

typedef GLint Attribute;
typedef GLint Uniform;

/// Program Object
class Program : public GLObject
{
public:
    Program();

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
    
    template <typename T, typename U>
    Program& SetUniformInt(const std::string& name, const T& x, const U& y)
    {
        return SetUniformInt(GetUniform(name), x, y);
    }
    template <typename T, typename U>
    Program& SetUniformFloat(const std::string& name, const T& x, const U& y)
    {
        return SetUniformFloat(GetUniform(name), (float)x, (float)y);
    }
    
    template <typename T, typename U, typename V>
    Program& SetUniformInt(const std::string& name, const T& x, const U& y, const V& z)
    {
        return SetUniformInt(GetUniform(name), x, y, z);
    }
    template <typename T, typename U, typename V>
    Program& SetUniformFloat(const std::string& name, const T& x, const U& y, const V& z)
    {
        return SetUniformFloat(GetUniform(name), (float)x, (float)y, (float)z);
    }
    
    template <typename T, typename U, typename V, typename W>
    Program& SetUniformInt(const std::string& name, const T& x, const U& y, const V& z, const W& w)
    {
        return SetUniformInt(GetUniform(name), x, y, z, w);
    }
    template <typename T, typename U, typename V, typename W>
    Program& SetUniformFloat(const std::string& name, const T& x, const U& y, const V& z, const W& w)
    {
        return SetUniformFloat(GetUniform(name), (float)x, (float)y, (float)z, (float)w);
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
    Program& SetUniformInt(const Uniform& uniform, const int* values, unsigned count);
    Program& SetUniformFloat(const Uniform& uniform, float value);
    Program& SetUniformFloat(const Uniform& uniform, float x, float y);
    Program& SetUniformFloat(const Uniform& uniform, float x, float y, float z);
    Program& SetUniformFloat(const Uniform& uniform, float x, float y, float z, float w);
    Program& SetUniformFloat(const Uniform& uniform, const float* values, unsigned count);
    
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
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    static GLuint s_boundProgram;
#endif
    
    bool _valid;
};

#define GLSL(verStr, x) "#version " verStr "\n" #x
#define GLSL150(x) GLSL("150", x)

