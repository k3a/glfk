/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/
#include "Shader.h"
#include <stdlib.h>

#ifdef GLFK_HAS_GLM
# include <glm/gtc/type_ptr.hpp>
#endif

BaseShader::BaseShader(GLenum shaderType) 
: _valid(false)
{
    AssignGLObject(glCreateShader(shaderType), glDeleteShader);
    PrintGLError("creating shader");
}
BaseShader& BaseShader::SetSource(std::string str)
{
    if (str.length() == 0) 
        printf("%s: empty source!\n", __FUNCTION__);

    const char* ptr = str.c_str();
    glShaderSource(*this, 1, &ptr, NULL);
    PrintGLError("setting shader source");
    return *this;
}
bool BaseShader::Compile()
{
    glCompileShader(*this);
    PrintGLError("compiling shader");

    GLint success = 0;
    glGetShaderiv(*this, GL_COMPILE_STATUS, &success);
    PrintGLError("getting compile status");

    _valid = success != GL_FALSE;
    return _valid;
}
std::string BaseShader::GetInfoLog()const
{
    std::string outLog;
    GLint logSize = 0;

    glGetShaderiv(*this, GL_INFO_LOG_LENGTH, &logSize);
    PrintGLError("getting shader iv");

    GLchar *errorLog = (GLchar *)malloc(logSize);
    glGetShaderInfoLog(*this, logSize, &logSize, errorLog);
    PrintGLError("getting shader log");
    outLog = errorLog;
    free(errorLog);

    return outLog;
}

//-----------------------------------------------

#ifdef GLFK_PREVENT_MULTIPLE_BIND
GLuint Program::s_boundProgram = 0;
#endif

Program::Program()
: _valid(false)
{
    AssignGLObject(glCreateProgram(), glDeleteProgram);
    PrintGLError("creating program");
}

Program& Program::AttachShader(const BaseShader& sh)
{
    glAttachShader(*this, sh);
    PrintGLError("attaching shader");
    return *this;
}

bool Program::Link()
{
    glLinkProgram(*this);
    PrintGLError("linking program");

    GLint success = 0;
    glGetProgramiv(*this, GL_LINK_STATUS, &success);
    PrintGLError("getting program link status");

    _valid = success != GL_FALSE;
    return _valid;
}

Program& Program::Validate()
{
    glValidateProgram(*this);
    return *this;
}

std::string Program::GetInfoLog()const
{
    std::string outLog;
    GLint logSize = 0;

    glGetProgramiv(*this, GL_INFO_LOG_LENGTH, &logSize);
    PrintGLError("getting program iv");

    GLchar *errorLog = (GLchar *)malloc(logSize);
    glGetProgramInfoLog(*this, logSize, &logSize, errorLog);
    PrintGLError("getting program info log");
    outLog = errorLog;
    free(errorLog);

    return outLog;
}

Program& Program::Use()
{
#ifdef GLFK_PREVENT_MULTIPLE_BIND
    if (s_boundProgram == *this)
        return *this;
    s_boundProgram = *this;
#endif
    glUseProgram(*this);
    PrintGLError("using program");
    return *this;
}

GLint Program::GetInt(GLenum pname)const
{
    GLint ret;
    glGetProgramiv(*this, pname, &ret);
    PrintGLError("glGetProgramiv");
    return ret;
}

Attribute Program::GetAttribute(const std::string& name)
{
    Attribute out = glGetAttribLocation( *this, name.c_str() );
    PrintGLError("getting attribute location");
    return out;
}

Uniform Program::GetUniform(const std::string& name)
{
    Uniform out = glGetUniformLocation(*this, name.c_str());
    PrintGLError("getting uniform location");
    return out;
}

Program& Program::SetUniformInt(const Uniform& uniform, int value)
{
    GLFK_AUTO_BIND();
    glUniform1i(uniform, value);
    PrintGLError("setting int uniform");
    return *this;
}

Program& Program::SetUniformInt(const Uniform& uniform, int x, int y)
{
    GLFK_AUTO_BIND();
    glUniform2i(uniform, x, y);
    PrintGLError("setting 2 int uniform");
    return *this;
}

Program& Program::SetUniformInt(const Uniform& uniform, int x, int y, int z)
{
    GLFK_AUTO_BIND();
    glUniform3i(uniform, x, y, z);
    PrintGLError("setting 3 int uniform");
    return *this;
}

Program& Program::SetUniformInt(const Uniform& uniform, int x, int y, int z, int w)
{
    GLFK_AUTO_BIND();
    glUniform4i(uniform, x, y, z, w);
    PrintGLError("setting 4 int uniform");
    return *this;
}

Program& Program::SetUniformInt(const Uniform& uniform, const int* values, unsigned count)
{
    GLFK_AUTO_BIND();
    glUniform1iv(uniform, count, values);
    PrintGLError("setting float array uniform");
    return *this;
}

Program& Program::SetUniformFloat(const Uniform& uniform, float value)
{
    GLFK_AUTO_BIND();
    glUniform1f(uniform, value);
    PrintGLError("setting float uniform");
    return *this;
}

Program& Program::SetUniformFloat(const Uniform& uniform, float x, float y)
{
    GLFK_AUTO_BIND();
    glUniform2f(uniform, x, y);
    PrintGLError("setting 2 float uniform");
    return *this;
}

Program& Program::SetUniformFloat(const Uniform& uniform, float x, float y, float z)
{
    GLFK_AUTO_BIND();
    glUniform3f(uniform, x, y, z);
    PrintGLError("setting 3 float uniform");
    return *this;
}

Program& Program::SetUniformFloat(const Uniform& uniform, float x, float y, float z, float w)
{
    GLFK_AUTO_BIND();
    glUniform4f(uniform, x, y, z, w);
    PrintGLError("setting 4 float uniform");
    return *this;
}

Program& Program::SetUniformFloat(const Uniform& uniform, const float* values, unsigned count)
{
    GLFK_AUTO_BIND();
    glUniform1fv(uniform, count, values);
    PrintGLError("setting float array uniform");
    return *this;
}

#ifdef GLFK_HAS_GLM
Program& Program::SetUniform(const Uniform& uniform, const glm::vec2& value)
{
    return SetUniformFloat(value.x, value.y);
}

Program& Program::SetUniform(const Uniform& uniform, const glm::vec3& value)
{
    return SetUniformFloat(value.x, value.y, value.z);
}

Program& Program::SetUniform(const Uniform& uniform, const glm::vec4& value)
{
    return SetUniformFloat(value.x, value.y, value.z, value.w);
}

Program& Program::SetUniform(const Uniform& uniform, const glm::vec2* values, unsigned count)
{
    GLFK_AUTO_BIND();
    glUniform2fv(uniform, count, (float*)values);
    PrintGLError("setting 2f array uniform");
    return *this;
}

Program& Program::SetUniform(const Uniform& uniform, const glm::vec3* values, unsigned count)
{
    GLFK_AUTO_BIND();
    glUniform3fv(uniform, count, (float*)values);
    PrintGLError("setting 3f array uniform");
    return *this;
}

Program& Program::SetUniform(const Uniform& uniform, const glm::vec4* values, unsigned count)
{
    GLFK_AUTO_BIND();
    glUniform4fv(uniform, count, (float*)values);
    PrintGLError("setting 4f array uniform");
    return *this;
}

Program& Program::SetUniform(const Uniform& uniform, const glm::mat3x3& value)
{
    GLFK_AUTO_BIND();
    glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
    PrintGLError("setting mat3x3 uniform");
    return *this;
}

Program& Program::SetUniform( const Uniform& uniform, const glm::mat4x4& value)
{
    GLFK_AUTO_BIND();
    glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
    PrintGLError("setting mmat 4x4 uniform");
    return *this;
}
#endif
