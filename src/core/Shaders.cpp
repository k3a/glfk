#include "Shaders.h"
#include <stdlib.h>

BaseShader::BaseShader(GLenum shaderType) 
: _valid(false)
{
	_shader = glCreateShader(shaderType);
	PrintGLError("creating shader");
}
BaseShader::~BaseShader()
{
	printf("deleting shader\n");
	glDeleteShader(_shader);
	PrintGLError("deleting shader");
}
BaseShader& BaseShader::SetSource(std::string str) 
{
	if (str.length() == 0) 
		printf("%s: empty source!\n", __FUNCTION__);

	const char* ptr = str.c_str();
	glShaderSource(_shader, 1, &ptr, NULL);
	PrintGLError("setting shader source");
	return *this;
}
bool BaseShader::Compile()
{
	glCompileShader(_shader);
	PrintGLError("compiling shader");

	GLint success = 0;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
	PrintGLError("getting compile status");

	_valid = success != GL_FALSE;
	return _valid;
}
std::string BaseShader::GetInfoLog()const
{
	std::string outLog;
    GLint logSize = 0;

    glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &logSize);
	PrintGLError("getting shader iv");

    GLchar *errorLog = (GLchar *)malloc(logSize);
    glGetShaderInfoLog(_shader, logSize, &logSize, errorLog);
	PrintGLError("getting shader log");
	outLog = errorLog;
    free(errorLog);

	return outLog;
}

//-----------------------------------------------

//-----------------------------------------------

Program::Program() 
: _valid(false)
{
	_program = glCreateProgram();
	PrintGLError("creating program");
}

Program::~Program()
{
	glDeleteProgram(_program);
	PrintGLError("deleting program");
}

Program& Program::AttachShader(const BaseShader& sh)
{
	glAttachShader(_program, sh._shader);
	PrintGLError("attaching shader");
	return *this;
}

bool Program::Link()
{
	glLinkProgram(_program);
	PrintGLError("linking program");

	GLint success = 0;
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	PrintGLError("getting program link status");

	_valid = success != GL_FALSE;
	return _valid;
}

std::string Program::GetInfoLog()const
{
	std::string outLog;
    GLint logSize = 0;

    glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &logSize);
	PrintGLError("getting program iv");

    GLchar *errorLog = (GLchar *)malloc(logSize);
    glGetProgramInfoLog(_program, logSize, &logSize, errorLog);
	PrintGLError("getting program info log");
	outLog = errorLog;
    free(errorLog);

    return outLog;
}

Program& Program::Use()
{
	glUseProgram(_program);
	PrintGLError("using program");
	return *this;
}

GLint Program::GetIntVar(GLenum pname)const
{
	GLint ret;
	glGetProgramiv(_program, pname, &ret);
	PrintGLError("glGetProgramiv");
	return ret;
}

