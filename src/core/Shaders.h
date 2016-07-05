#pragma once

#include "Renderer.h"
#include "Utils.h"
#include <string>

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

private:
	GLuint _program;
	bool _valid;
};
