/*-
Minimalistic and Modular OpenGL C++ Framework
GLFK LICENSE (BSD-based) - please see LICENSE.md
-*/
#pragma once

#include "Renderer.h"
#include "Utils.h"

#include <string>
#include <vector>

/// Class encapsulating Shader Object
class BaseShader : public GLObject
{
    friend class Program;

public:
    BaseShader(GLenum shaderType);
    BaseShader(GLenum shaderType, std::string source);

    /// Compiles the shader and returns the compile status
    bool Compile();
    
    /// Returns the shader info log
    std::string GetInfoLog()const;
    
    /// Sets the shader source code
    BaseShader& SetSource(std::string str);
    
    /// Returns true if the shader has been compiled successfuly and is ready to be linked in a program.
    bool IsValid()const{ return _valid; };

private:
    bool _valid;
};

/// Program object of type GL_VERTEX_SHADER
class VertexShader : public BaseShader
{
public:
    VertexShader() : BaseShader(GL_VERTEX_SHADER) {};
    VertexShader(std::string source) : BaseShader(GL_VERTEX_SHADER, source) {};
    
    static VertexShader FromFile(const char* path){
        return VertexShader(ReadFile(path));
    }
    
    // helpers 
    static unsigned GetMaxVertexAttributes(){ return Renderer::GetInt(GL_MAX_VERTEX_ATTRIBS); };
};

/// Program object of type GL_FRAGMENT_SHADER
class FragmentShader : public BaseShader
{
public:
    FragmentShader() : BaseShader(GL_FRAGMENT_SHADER) {};
    FragmentShader(std::string source) : BaseShader(GL_FRAGMENT_SHADER, source) {};
    
    static FragmentShader FromFile(const char* path){
        return FragmentShader(ReadFile(path));
    }
};
/// Alias of FragmentShader
typedef FragmentShader PixelShader;

/// Program object of type GL_COMPUTE_SHADER
class ComputeShader : public BaseShader
{
public:
    ComputeShader() : BaseShader(GL_COMPUTE_SHADER) {};
    ComputeShader(std::string source) : BaseShader(GL_COMPUTE_SHADER, source) {};
    
    static ComputeShader FromFile(const char* path){
        return ComputeShader(ReadFile(path));
    }
};

/// Program object of type GL_GEOMETRY_SHADER
class GeometryShader : public BaseShader
{
public:
    GeometryShader() : BaseShader(GL_GEOMETRY_SHADER) {};
    GeometryShader(std::string source) : BaseShader(GL_GEOMETRY_SHADER, source) {};
    
    static GeometryShader FromFile(const char* path){
        return GeometryShader(ReadFile(path));
    }
};

/// Program object of type GL_TESS_EVALUATION_SHADER
class TessEvaluationShader : public BaseShader
{
public:
    TessEvaluationShader() : BaseShader(GL_TESS_EVALUATION_SHADER) {};
    TessEvaluationShader(std::string source) : BaseShader(GL_TESS_EVALUATION_SHADER, source) {};
    
    static TessEvaluationShader FromFile(const char* path){
        return TessEvaluationShader(ReadFile(path));
    }
};

/// Program object of type GL_TESS_CONTROL_SHADER
class TessControlShader : public BaseShader
{
public:
    TessControlShader() : BaseShader(GL_TESS_CONTROL_SHADER) {};
    TessControlShader(std::string source) : BaseShader(GL_TESS_CONTROL_SHADER, source) {};
    
    static TessControlShader FromFile(const char* path){
        return TessControlShader(ReadFile(path));
    }
};

typedef GLint Attribute;
typedef GLint Uniform;

struct UniformInfo {
    std::string name;
    ShaderUniformType::E type;
    GLint size;
};
struct AttributeInfo {
    std::string name;
    ShaderAttribType::E type;
    GLint size;
};

/// Program Object
class Program : public GLObject
{
public:
    /// Empty program object
    Program();
    
    /// Program object with supplied shader. Shader will be compiled if not compiled already.
    Program(BaseShader& sh);
    /// Program with supplied shaders. Shader will be compiled if not compiled already.
    Program(BaseShader& sh1, BaseShader& sh2);
    /// Program with supplied shaders. Shader will be compiled if not compiled already.
    Program(BaseShader& sh1, BaseShader& sh2, BaseShader& sh3);
    
    /// Program object with supplied shader. Shader must be compiled manually before linking.
    Program(const BaseShader& sh);
    /// Program with supplied shaders. Shaders must be compiled manually before linking.
    Program(const BaseShader& sh1, const BaseShader& sh2);
    /// Program with supplied shaders. Shaders must be compiled manually before linking.
    Program(const BaseShader& sh1, const BaseShader& sh2, const BaseShader& sh3);
    
    /// Attachs a shader object into the program. Shader will be compiled if not compiled already.
    Program& AttachShader(BaseShader& sh);
    
    /// Attachs a shader object into the program. Shader must be compiled manually before linking.
    Program& AttachShader(const BaseShader& sh);
    
    /// Links the attached shaders. Possible errors returned by GetInfoLog().
    bool Link();
    
    /// Validates the program can run in the current GL state. Possible errors returned by GetInfoLog().
    Program& Validate();
    
    /// Return linking info log of the program
    std::string GetInfoLog()const;
    
    /// Returns true if the program has been linked successfuly and is ready to be used.
    bool IsValid()const{return _valid;};

    /// Use the program
    Program& Use();
    
    /// Alias of Use
    Program& Bind(){ return Use(); };
    
    /// Launches one or more compute work groups 
    Program& DispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
    
    /// Associates a user-defined attribute variable with a generic vertex attribute index. Link() is necessary for it to go into effect.
    Program& BindAttribLocation(GLuint attribIndex, const GLchar *name);
    
    /// Returns integer param of the program object
    GLint GetInt(GLenum pname)const;
    
    /// Returns attribute location for the specified name. Also see BindAttribLocation().
    Attribute GetAttribute(const std::string& name);
    
    /// Returns attribute info
    AttributeInfo GetAttributeInfo(const Attribute& a);
    
    /// Returns uniform for the specified name
    Uniform GetUniform(const std::string& name);
    
    /// Returns name of the uniform
    std::string GetUniformName(const Uniform& u);
    
    /// Returns uniform info
    UniformInfo GetUniformInfo(const Uniform& u);
    
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
    
    /// Define an array of buffers into which outputs from the fragment shader data will be written.
    /// Uses glDrawBuffers() and setting persists until you change it.
    static void SetDrawBuffers(unsigned num, DrawBufferType::E type, ...);
    
private:
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    static GLuint s_boundProgram;
#endif
    
    bool _valid;
};

#define GLSL(verStr, x) "#version " verStr "\n" #x
// OpenGL > 3.2
#define GLSL150(x) GLSL("150", x)
#define GLSL330(x) GLSL("330", x)
#define GLSL400(x) GLSL("400", x)
#define GLSL410(x) GLSL("410", x)
#define GLSL420(x) GLSL("420", x)
#define GLSL430(x) GLSL("430", x)
// OpenGL ES
#define GLSL100(x) GLSL("100", x) //2.0
#define GLSL300(x) GLSL("300", x) //3.0

